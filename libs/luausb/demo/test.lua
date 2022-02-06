local usb = require 'usb'

local context = assert(usb.init())

--[[
print("logitech mouse")

local handle = context:open_device_with_vid_pid(0x046d, 0xc049)
if handle:kernel_driver_active(0) then
	print("detaching kernel driver")
	assert(handle:detach_kernel_driver(0))
end

print()
--]]

print("logitech trackball")

local handle = context:open_device_with_vid_pid(0x046d, 0xc404)
if handle:kernel_driver_active(0) then
	print("detaching kernel driver")
	assert(handle:detach_kernel_driver(0))
end

--[[
handle:control_transfer(
	LIBUSB_RECIPIENT_ENDPOINT, LIBUSB_REQUEST_TYPE_STANDARD, LIBUSB_ENDPOINT_OUT,
	LIBUSB_REQUEST_SET_FEATURE,
	1,
)
--]]
--[[
for i=1,100 do
	local result,msg = handle:interrupt_transfer(0x81, 8, 0)
	if result then
		local bytes = {string.byte(result, 1, #result)}
		for _,byte in ipairs{string.byte(result, 1, #result)} do
			io.write(string.format("%02x", byte))
		end
		io.write("\n")
	end
end
--]]

--print(handle:interrupt_transfer(0x01, "\000\000\000\000\000\000\000\000", 0))
--[[
print(#handle:control_transfer(
	bit.bor(
		usb.ENDPOINT_IN,
		usb.REQUEST_TYPE_STANDARD,
		usb.RECIPIENT_INTERFACE),
	usb.REQUEST_GET_DESCRIPTOR,
	usb.DT_REPORT * 2^8,
	0,
	16,
	0))
--]]
--[[
print(handle:control_transfer(
	bit.bor(
		usb.ENDPOINT_OUT,
		usb.REQUEST_TYPE_STANDARD,
		usb.RECIPIENT_INTERFACE),
	usb.REQUEST_SET_FEATURE,
	0x0,
	0,
	"\000\000\000\000\000\000\000\000",
	0))
--]]

print()

print("motor board")

local handle = context:open_device_with_vid_pid(0xd00b, 0x0001)

print(handle)

if handle:kernel_driver_active(0) then
	print("detaching kernel driver")
	assert(handle:detach_kernel_driver(0))
end

print("claiming interface")
assert(handle:claim_interface(0))

print("transfering some data")
--[[
for i=1,100 do
	local result,msg = handle:interrupt_transfer(0x81, 8, 0)
	if result then
		local bytes = {string.byte(result, 1, #result)}
		for _,byte in ipairs{string.byte(result, 1, #result)} do
			io.write(string.format("%02x", byte))
		end
		io.write("\n")
	end
end
--]]

print("releasing interface")
print(handle:release_interface(0))

--assert(handle:attach_kernel_driver(0))

print("exited successfully")
