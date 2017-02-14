
#ifndef _LO_CPP_H_
#define _LO_CPP_H_

#include <lo/lo.h>
#include <lo/lo_throw.h>

#include <functional>
#include <memory>
#include <list>
#include <unordered_map>
#include <string>
#include <sstream>
#include <initializer_list>

#define LO_ADD_METHOD_RT(ht, argtypes, args, rt, r, r1, r2)             \
    template <typename H>                                               \
    auto add_method(const string_type path, const string_type types, H&& h) \
    -> rt const                                                         \
    {                                                                   \
        std::string key = std::string(path._s?:"") + "," + (types._s?:""); \
        _handlers[key].push_front(                                      \
            std::unique_ptr<handler>(new handler_type<r ht>(h)));       \
        _add_method(path, types,                                        \
            [](const char *path, const char *types,                     \
               lo_arg **argv, int argc, void *msg,                      \
               void *data)->int                                         \
            {                                                           \
                r1 (*static_cast<handler_type<r ht>*>(data)) args; \
                r2;                                                     \
            }, _handlers[key].front().get());                           \
    }

#define RT_INT(argtypes) \
    typename std::enable_if<std::is_same<decltype(h argtypes), int>::value, void>::type
#define RT_VOID(argtypes) \
    typename std::enable_if<std::is_same<decltype(h argtypes), void>::value, void>::type

#define LO_ADD_METHOD(ht, argtypes, args)                         \
    LO_ADD_METHOD_RT(ht, argtypes, args,                          \
                     RT_INT(argtypes), int, return,);             \
    LO_ADD_METHOD_RT(ht, argtypes, args,                          \
                     RT_VOID(argtypes), void, , return 0)

namespace lo {

    // Helper classes to allow polymorphism on "const char *",
    // "std::string", and "int".
    class string_type {
      public:
        string_type(const char *s=0) { _s = s; }
        string_type(const std::string &s) { _s = s.c_str(); }
        operator const char*() const { return _s; }
        const char *_s;
    };

    class num_string_type : public string_type {
      public:
      num_string_type(const char *s) : string_type(s) {}
      num_string_type(const std::string &s) : string_type(s) {}
        num_string_type(int n) { std::ostringstream ss; ss << n;
            _p.reset(new std::string(ss.str())); _s = _p->c_str(); }
        std::unique_ptr<std::string> _p;
    };

    class ServerThread;

    class Address
    {
      public:
        Address(const string_type &host, const num_string_type &port,
                int proto=LO_UDP)
          { address = lo_address_new_with_proto(proto, host, port); owned=true; }

        Address(const string_type &url)
          { address = lo_address_new_from_url(url); owned=true; }

        Address(lo_address a, bool _owned=true)
          { address = a; owned=_owned; }

        ~Address()
          { if (address && owned) lo_address_free(address); }

        Address& operator=(Address b) { b.swap(*this); return *this; }
        void swap(Address& b) throw () { std::swap(this->address, b.address); }

        int ttl() const
          { return lo_address_get_ttl(address); }

        void set_ttl(int ttl)
          { lo_address_set_ttl(address, ttl); }

        int send(const string_type &path) const
          { return lo_send(address, path, ""); }

        // In these functions we append "$$" to the type string, which
        // simply instructs lo_message_add_varargs() not to use
        // LO_MARKER checking at the end of the argument list.
        int send(const string_type &path, const string_type &type, ...) const
        {
            va_list q;
            va_start(q, type);
            lo_message m = lo_message_new();
            std::string t = std::string(type) + "$$";
            lo_message_add_varargs(m, t.c_str(), q);
            int r = lo_send_message(address, path, m);
            lo_message_free(m);
            return r;
        }

        int send(lo_timetag ts, const string_type &path,
                 const string_type &type, ...) const
        {
            va_list q;
            va_start(q, type);
            lo_message m = lo_message_new();
            std::string t = std::string(type) + "$$";
            lo_message_add_varargs(m, t.c_str(), q);
            lo_bundle b = lo_bundle_new(ts);
            lo_bundle_add_message(b, path, m);
            int r = lo_send_bundle(address, b);
            lo_bundle_free_messages(b);
            return r;
        }

        int send(const string_type &path, lo_message m) const
            { return lo_send_message(address, path, m); }

        int send(lo_bundle b)
            { return lo_send_bundle(address, b); }

        int send_from(lo::ServerThread &from, const string_type &path,
                      const string_type &type, ...) const;

        int send_from(lo_server from, const string_type &path,
                      const string_type &type, ...) const
        {
            va_list q;
            va_start(q, type);
            lo_message m = lo_message_new();
            std::string t = std::string(type) + "$$";
            lo_message_add_varargs(m, t.c_str(), q);
            int r = lo_send_message_from(address, from, path, m);
            lo_message_free(m);
            return r;
        }

        int send_from(lo_server from, lo_timetag ts, 
                      const string_type &path,
                      const string_type &type, ...) const
        {
            va_list q;
            va_start(q, type);
            lo_message m = lo_message_new();
            std::string t = std::string(type) + "$$";
            lo_message_add_varargs(m, t.c_str(), q);
            lo_bundle b = lo_bundle_new(ts);
            lo_bundle_add_message(b, path, m);
            int r = lo_send_bundle_from(address, from, b);
            lo_bundle_free_messages(b);
            return r;
        }

        int send_from(lo_server from, const string_type &path, lo_message m) const
            { return lo_send_message_from(address, from, path, m); }

        int send(lo_server from, lo_bundle b) const
            { return lo_send_bundle_from(address, from, b); }

        int get_errno() const
          { return lo_address_errno(address); }

        std::string errstr() const
          { return std::string(lo_address_errstr(address)?:""); }

        std::string hostname() const
          { return std::string(lo_address_get_hostname(address)?:""); }

        std::string port() const
          { return std::string(lo_address_get_port(address)?:""); }

        int protocol() const
          { return lo_address_get_protocol(address); }

        std::string url() const
          { return std::string(lo_address_get_url(address)?:""); }

        std::string iface() const
          { return std::string(lo_address_get_iface(address)?:""); }

        void set_iface(const string_type &iface, const string_type &ip)
          { lo_address_set_iface(address, iface._s?:0, ip._s?:0); }

        int set_tcp_nodelay(int enable)
          { return lo_address_set_tcp_nodelay(address, enable); }

        int set_stream_slip(int enable)
          { return lo_address_set_stream_slip(address, enable); }

        operator lo_address() const
            { return address; }

      protected:
        lo_address address;
        bool owned;
    };

    class Message
    {
      public:
        Message()
            : message(lo_message_new()) { lo_message_incref(message); }

        Message(lo_message m)
            : message(m) { if (m) { lo_message_incref(m); } }

        Message(const Message &m)
            : message(m.message) { if (m.message)
                                       lo_message_incref(m.message); }

        Message(const string_type &types, ...)
        {
            message = lo_message_new();
            lo_message_incref(message);
            va_list q;
            va_start(q, types);
            std::string t(std::string(types)+"$$");
            add_varargs(t.c_str(), q);
        }

        ~Message()
            { if (message) lo_message_free(message); }

        Message& operator=(Message m) { m.swap(*this); return *this; }
        void swap(Message& m) throw () { std::swap(this->message, m.message); }

        int add(const string_type &types, ...)
        {
            va_list q;
            va_start(q, types);
            std::string t(std::string(types)+"$$");
            return add_varargs(t.c_str(), q);
        }

        int add_varargs(const string_type &types, va_list ap)
            { return lo_message_add_varargs(message, types, ap); }

        int add_int32(int32_t a)
            { return lo_message_add_int32(message, a); }

        int add_float(float a)
            { return lo_message_add_float(message, a); }

        int add_string(const string_type &a)
            { return lo_message_add_string(message, a); }

        int add_blob(lo_blob a)
            { return lo_message_add_blob(message, a); }

        int add_int64(int64_t a)
            { return lo_message_add_int64(message, a); }

        int add_timetag(lo_timetag a)
            { return lo_message_add_timetag(message, a); }

        int add_double(double a)
            { return lo_message_add_double(message, a); }

        int add_symbol(const string_type &a)
            { return lo_message_add_symbol(message, a); }

        int add_char(char a)
            { return lo_message_add_char(message, a); }

        int add_midi(uint8_t a[4])
            { return lo_message_add_midi(message, a); }

        int add_bool(bool b)
            { if (b)
                return lo_message_add_true(message);
              else
                return lo_message_add_false(message); }

        int add_true()
            { return lo_message_add_true(message); }

        int add_false()
            { return lo_message_add_false(message); }

        int add_nil()
            { return lo_message_add_nil(message); }

        int add_infinitum()
            { return lo_message_add_infinitum(message); }

        // Note, for polymorphic versions of "add", below, we can't do
        // this for "string" or "symbol" types, since it is ambiguous
        // with "add(types, ...)" above.

        int add(int32_t a)
            { return lo_message_add_int32(message, a); }

        int add(float a)
            { return lo_message_add_float(message, a); }

        int add(lo_blob a)
            { return lo_message_add_blob(message, a); }

        int add(int64_t a)
            { return lo_message_add_int64(message, a); }

        int add(lo_timetag a)
            { return lo_message_add_timetag(message, a); }

        int add(double a)
            { return lo_message_add_double(message, a); }

        int add(char a)
            { return lo_message_add_char(message, a); }

        int add(uint8_t a[4])
            { return lo_message_add_midi(message, a); }

        int add(bool b)
            { if (b)
                return lo_message_add_true(message);
              else
                return lo_message_add_false(message); }

        Address source() const
            { return Address(lo_message_get_source(message), false); }

        lo_timetag timestamp() const
            { return lo_message_get_timestamp(message); }

        std::string types() const
            { return std::string(lo_message_get_types(message)?:""); }

        int argc() const
            { return lo_message_get_argc(message); }

        lo_arg **argv() const
            { return lo_message_get_argv(message); }

        size_t length(const string_type &path) const
            { return lo_message_length(message, path); }

        void *serialise(const string_type &path, void *to, size_t *size) const
            { return lo_message_serialise(message, path, to, size); }

        typedef std::pair<int, Message> maybe;

        static
        maybe deserialise(void *data, size_t size)
            { int result = 0;
              lo_message m = lo_message_deserialise(data, size, &result);
              return maybe(result, m); }

        void print() const
            { lo_message_pp(message); }

        lo::Message clone() const
            { return lo::Message(lo_message_clone(message)); }

        operator lo_message() const
            { return message; }

      protected:
        lo_message message;
    };

    class Server
    {
      public:
        Server(lo_server s) : server(s) {}

        template <typename E>
        Server(const num_string_type &port, E&& e)
            : Server(lo_server_new(port,
              [](int num, const char *msg, const char *where){
                auto h = static_cast<handler_error*>(lo_error_get_context());
                (*h)(num, msg, where);
              }))
        {
            if (server) {
                lo_server_set_error_context(server,
					    (_error_handler = std::unique_ptr<handler>(
										       new handler_error(e))).get());
            }
        }

        template <typename E>
        Server(const num_string_type &port, int proto, E&& e=0)
            : Server(lo_server_new_with_proto(port, proto,
              [](int num, const char *msg, const char *where){
                auto h = static_cast<handler_error*>(lo_error_get_context());
                (*h)(num, msg, where);
              }))
        {
            if (server) {
                lo_server_set_error_context(server,
					    (_error_handler = std::unique_ptr<handler>(
										       new handler_error(e))).get());
            }
        }

        template <typename E>
        Server(const string_type &group, const num_string_type &port,
               const string_type &iface=0, const string_type &ip=0, E&& e=0)
            : Server((!iface._s || !ip._s)
                     ? lo_server_new_multicast_iface(group, port, iface, ip,
                           [](int num, const char *msg, const char *where){
                               auto h = static_cast<handler_error*>(lo_error_get_context());
                               (*h)(num, msg, where);
                           })
                     : lo_server_new_multicast(group, port,
                           [](int num, const char *msg, const char *where){
                               auto h = static_cast<handler_error*>(lo_error_get_context());
                               (*h)(num, msg, where);
                       }))
        {
            if (server) {
                lo_server_set_error_context(server,
					    (_error_handler = std::unique_ptr<handler>(
										       new handler_error(e))).get());
            }
        }

        Server(const num_string_type &port, lo_err_handler err_h=0)
            : Server(lo_server_new(port, err_h)) {}

        Server(const num_string_type &port, int proto, lo_err_handler err_h=0)
            : Server(lo_server_new_with_proto(port, proto, err_h)) {}

        Server(const string_type &group, const num_string_type &port,
               const string_type &iface="", const string_type &ip="", lo_err_handler err_h=0)
            : Server((iface._s || ip._s)
                     ? lo_server_new_multicast_iface(group, port,
                                                     iface._s?:0,
                                                     ip._s?:0, err_h)
                     : lo_server_new_multicast(group, port, err_h)) {}

        virtual ~Server()
            { if (server) lo_server_free(server); }

        bool is_valid() const { return server!=nullptr; }

        // Regular old liblo method handlers
        void add_method(const string_type &path, const string_type &types,
                        lo_method_handler h, void *data) const
            { _add_method(path, types, h, data); }

        // Alternative callback prototypes
        LO_ADD_METHOD( (const char*, const char*, lo_arg**, int),
                       ((char*)0, (char*)0, (lo_arg**)0, (int)0),
                       (path, types, argv, argc) );
        LO_ADD_METHOD( (const char*, lo_arg**, int),
                       ((char*)0, (lo_arg**)0, (int)0),
                       (types, argv, argc) );
        LO_ADD_METHOD( (const char*, lo_arg**, int, const Message&),
                       ((char*)0, (lo_arg**)0, (int)0, Message((lo_message)0)),
                       (types, argv, argc, Message(msg)) );
        LO_ADD_METHOD( (const char*, const Message&),
                       ((char*)0, Message((lo_message)0)),
                       (path, Message(msg)) );
        LO_ADD_METHOD( (lo_arg**, int), ((lo_arg**)0, (int)0), (argv, argc) )
        LO_ADD_METHOD( (lo_arg**, int, const Message& ),
                       ((lo_arg**)0, (int)0, Message((lo_message)0)),
                       (argv, argc, Message(msg)) );
        LO_ADD_METHOD( (const Message&),
                       (Message((lo_message)0)),
                       (Message(msg)) );
        LO_ADD_METHOD( (), (), () );

        void del_method(const string_type &path, const string_type &typespec)
        {
            _handlers.erase(std::string(path._s?:"") + ","
                            + (typespec._s?:""));
            lo_server_del_method(server, path, typespec);
        }

        int dispatch_data(void *data, size_t size)
            { return lo_server_dispatch_data(server, data, size); }

        int wait(int timeout)
            { return lo_server_wait(server, timeout); }

        int recv()
            { return lo_server_recv(server); }

        int recv(int timeout)
            { return lo_server_recv_noblock(server, timeout); }

        int add_bundle_handlers(lo_bundle_start_handler sh,
                                lo_bundle_end_handler eh,
                                void *user_data)
        {
            return lo_server_add_bundle_handlers(server, sh, eh, user_data);
        }

        template <typename S, typename E>
        int add_bundle_handlers(S&& s, E&& e)
        {
            _bundle_handlers.reset(new std::pair<handler_bundle_start,
                                                 handler_bundle_end>(
                                       handler_bundle_start(s),
                                       handler_bundle_end(e)));
            return lo_server_add_bundle_handlers(
                server,
                [](lo_timetag time, void *user_data)->int{
                    auto h = (std::pair<handler_bundle_start,
                                        handler_bundle_end>*) user_data;
                    h->first(time);
                    return 0;
                },
                [](void *user_data)->int{
                    auto h = (std::pair<handler_bundle_start,
                                        handler_bundle_end>*) user_data;
                    h->second();
                    return 0;
                },
                _bundle_handlers.get());
        }

        int socket_fd() const
            { return lo_server_get_socket_fd(server); }

        int port() const
            { return lo_server_get_port(server); }

        int protocol() const
            { return lo_server_get_protocol(server); }

        std::string url() const
            { return std::string(lo_server_get_url(server)?:""); }

        int enable_queue(int queue_enabled,
                         int dispatch_remaining=1)
            { return lo_server_enable_queue(server,
                                            queue_enabled,
                                            dispatch_remaining); }

        int events_pending() const
            { return lo_server_events_pending(server); }

        double next_event_delay() const
            { return lo_server_next_event_delay(server); }

        operator lo_server() const
            { return server; }

      protected:
        lo_server server;

        friend class ServerThread;

        class handler {};
        template <typename T>
        class handler_type : public handler, public std::function<T> {
          public: template<typename H>handler_type(H&& h) : std::function<T>(h) {}
        };
        typedef handler_type<void(int, const char *, const char *)> handler_error;
        typedef handler_type<void(int, const std::string&, const std::string&)> handler_error_s;
        typedef handler_type<void(lo_timetag)> handler_bundle_start;
        typedef handler_type<void()> handler_bundle_end;

        // Keep std::functions here so they are freed correctly
        std::unordered_map<std::string,
            std::list<std::unique_ptr<handler>>> _handlers;
        std::unique_ptr<handler> _error_handler;
        std::unique_ptr<std::pair<handler_bundle_start,
                                  handler_bundle_end>> _bundle_handlers;

        virtual void _add_method(const char *path, const char *types,
                        lo_method_handler h, void *data) const
        {
            lo_server_add_method(server, path, types, h, data);
        }
    };

    class ServerThread : public Server
    {
      public:
        ServerThread(const num_string_type &port, lo_err_handler err_h=0)
            : Server(lo_server_thread_get_server(
                  server_thread = lo_server_thread_new(port, err_h))) {}

        template <typename E>
        ServerThread(const num_string_type &port, E&& e)
            : Server(lo_server_thread_get_server(
                  server_thread = lo_server_thread_new(port,
                  [](int num, const char *msg, const char *where){
                      auto h = static_cast<handler_error*>(lo_error_get_context());
                      (*h)(num, msg, where);})))
            {
                if (server_thread) {
                    auto h = new handler_error(e);
                    _error_handler.reset(h);
                    lo_server_thread_set_error_context(server_thread, h);
                }
            }

        ServerThread(const num_string_type &port, int proto, lo_err_handler err_h)
            : Server(lo_server_thread_get_server(
                  server_thread = lo_server_thread_new_with_proto(port, proto, err_h))) {}

        virtual ~ServerThread()
            { server = 0;
              if (server_thread) lo_server_thread_free(server_thread); }

        void start() { lo_server_thread_start(server_thread); }
        void stop() { lo_server_thread_stop(server_thread); }

        operator lo_server_thread() const
            { return server_thread; }

      protected:
        lo_server_thread server_thread;

        // Regular old liblo method handlers
        virtual void _add_method(const char *path, const char *types,
                                 lo_method_handler h, void *data) const
        {
            lo_server_thread_add_method(server_thread, path, types, h, data);
        }
    };

	// This function needed since lo::ServerThread doesn't
	// properly auto-upcast to lo::Server -> lo_server.  (Because
	// both lo_server and lo_serverthread are typedef'd as void*)
	int Address::send_from(lo::ServerThread &from, const string_type &path,
						   const string_type &type, ...) const
	{
		va_list q;
		va_start(q, type);
		lo_message m = lo_message_new();
		std::string t = std::string(type) + "$$";
		lo_message_add_varargs(m, t.c_str(), q);
		lo_server s = static_cast<lo::Server&>(from);
		int r = lo_send_message_from(address, s, path, m);
		lo_message_free(m);
		return r;
	}

    class Blob
    {
      public:
        Blob(int32_t size, const void *data=0)
            : blob(lo_blob_new(size, data)) {}

        template <typename T>
        Blob(const T &t)
            : blob(lo_blob_new(t.size()*sizeof(t[0]), &t[0])) {}

        virtual ~Blob()
            { lo_blob_free(blob); }

        Blob& operator=(Blob b) { b.swap(*this); return *this; }
        void swap(Blob& b) throw () { std::swap(this->blob, b.blob); }

        uint32_t datasize() const
            { return lo_blob_datasize(blob); }

        void *dataptr() const
            { return lo_blob_dataptr(blob); }

        uint32_t size() const
            { return lo_blobsize(blob); }

        operator lo_blob() const
            { return blob; };

      protected:
        lo_blob blob;
    };

    struct PathMsg
    {
        PathMsg() {}
        PathMsg(const string_type _path, const Message& _msg)
          : path(_path), msg(_msg) {}
        std::string path;
        Message msg;
    };

    class Bundle
    {
      public:
        template <typename T>
        struct ElementT
        {
            ElementT()
            : type((lo_element_type)0), pm("", 0), bundle((lo_bundle)0) {}
            ElementT(const string_type _path, const Message& _msg)
              : type(LO_ELEMENT_MESSAGE),
                pm(PathMsg(_path, _msg)),
                bundle((lo_bundle)0) {}
            ElementT(const T& _bundle)
              : type(LO_ELEMENT_BUNDLE), pm("", 0), bundle(_bundle) {}
            lo_element_type type;
            PathMsg pm;
            T bundle;
        };
        typedef ElementT<Bundle> Element;

        Bundle() { bundle = lo_bundle_new(LO_TT_IMMEDIATE); lo_bundle_incref(bundle); }

        Bundle(lo_timetag tt)
            : bundle(lo_bundle_new(tt)) { lo_bundle_incref(bundle); }

        Bundle(lo_bundle b)
            : bundle(b) { if (b) { lo_bundle_incref(b); } }

        Bundle(const string_type &path, lo_message m,
               lo_timetag tt=LO_TT_IMMEDIATE)
            : bundle(lo_bundle_new(tt))
        {
            lo_bundle_incref(bundle);
            lo_bundle_add_message(bundle, path, m);
        }

        Bundle(const std::initializer_list<Element> &elements,
               lo_timetag tt=LO_TT_IMMEDIATE)
            : bundle(lo_bundle_new(tt))
        {
            lo_bundle_incref(bundle);
            for (auto const &e : elements) {
                if (e.type == LO_ELEMENT_MESSAGE) {
                    lo_bundle_add_message(bundle, e.pm.path.c_str(), e.pm.msg);
                }
                else if (e.type == LO_ELEMENT_BUNDLE) {
                    lo_bundle_add_bundle(bundle, e.bundle);
                }
            }
        }

        Bundle(const Bundle &b)
            : Bundle((lo_bundle)b) {}

        ~Bundle()
            { if (bundle) lo_bundle_free_recursive(bundle); }

        Bundle& operator=(Bundle b) { b.swap(*this); return *this; }
        void swap(Bundle& b) throw () { std::swap(this->bundle, b.bundle); }

        int add(const string_type &path, lo_message m)
            { return lo_bundle_add_message(bundle, path, m); }

        int add(const lo_bundle b)
            { return lo_bundle_add_bundle(bundle, b); }

        size_t length() const
            { return lo_bundle_length(bundle); }

        unsigned int count() const
            { return lo_bundle_count(bundle); }

        lo_message get_message(int index, const char **path=0) const
            { return lo_bundle_get_message(bundle, index, path); }

        Message get_message(int index, std::string &path) const
            { const char *p;
              lo_message m=lo_bundle_get_message(bundle, index, &p);
              path = p?:0;
              return Message(m); }

        PathMsg get_message(int index) const
            { const char *p;
              lo_message m = lo_bundle_get_message(bundle, index, &p);
              return PathMsg(p?:0, m); }

        Bundle get_bundle(int index) const
            { return lo_bundle_get_bundle(bundle, index); }

        Element get_element(int index, const char **path=0) const
            {
                switch (lo_bundle_get_type(bundle, index)) {
                case LO_ELEMENT_MESSAGE: {
                    const char *p;
                    lo_message m = lo_bundle_get_message(bundle, index, &p);
                    return Element(p, m);
                }
                case LO_ELEMENT_BUNDLE:
                    return Element(lo_bundle_get_bundle(bundle, index));
                default:
                    return Element();
                }
            }

        lo_timetag timestamp()
            { return lo_bundle_get_timestamp(bundle); }

        void *serialise(void *to, size_t *size) const
            { return lo_bundle_serialise(bundle, to, size); }

        void print() const
            { lo_bundle_pp(bundle); }

        operator lo_bundle() const
            { return bundle; }

      protected:
        lo_bundle bundle;
    };

    std::string version() {
        char str[32];
        lo_version(str, 32, 0, 0, 0, 0, 0, 0, 0);
        return std::string(str);
    }

    lo_timetag now() { lo_timetag tt; lo_timetag_now(&tt); return tt; }
    lo_timetag immediate() { return LO_TT_IMMEDIATE; }
};

#endif // _LO_CPP_H_
