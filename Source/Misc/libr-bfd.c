/*
 *
 *  Copyright (c) 2008-2011 Erich Hoover
 *
 *  libr libbfd Backend - Add resources into ELF binaries using libbfd
 *
 * *** PLEASE READ THE README FILE FOR LICENSE DETAILS SPECIFIC TO THIS FILE ***
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * To provide feedback, report bugs, or otherwise contact me:
 * ehoover at mines dot edu
 *
 */
#ifdef LINUX
#include "libr.h"
/* File access */
#include <fcntl.h>

/* Safe rename requires some errno() knowledge */
#include <errno.h>

#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Build the libr_file handle for processing with libbfd
 */
libr_intstatus open_handles(libr_file *file_handle, char *filename, libr_access_t access)
{
	bfd *handle = NULL;

	handle = bfd_openr(filename, "default");
	if(!handle)
		RETURN(LIBR_ERROR_OPENFAILED, "Failed to open input file");
	if(!bfd_check_format(handle, bfd_object))
		RETURN(LIBR_ERROR_WRONGFORMAT, "Invalid input file format: not a libbfd object");
	if(bfd_get_flavour(handle) != bfd_target_elf_flavour)
		RETURN(LIBR_ERROR_WRONGFORMAT, "Invalid input file format: not an ELF file");
	bfd_set_error(bfd_error_no_error);
	file_handle->filename = filename;
	file_handle->bfd_read = handle;
	file_handle->access = access;
	if(access == LIBR_READ_WRITE)
	{
		struct stat file_stat;
		int fd;

		/* Check for write permission on the file */
		fd = open(filename, O_WRONLY);
		if(fd == ERROR)
			RETURN(LIBR_ERROR_WRITEPERM, "No write permission for file");
		close(fd);
		/* Obtain the access mode of the input file */
		if(stat(filename, &file_stat) == ERROR)
			RETURN(LIBR_ERROR_NOSIZE, "Failed to obtain file size");
		file_handle->filemode = file_stat.st_mode;
		file_handle->fileowner = file_stat.st_uid;
		file_handle->filegroup = file_stat.st_gid;
		/* Open a temporary file with the same settings as the input file */
		strcpy(file_handle->tempfile, LIBR_TEMPFILE);
		file_handle->fd_handle = mkstemp(file_handle->tempfile);
		handle = bfd_openw(file_handle->tempfile, bfd_get_target(file_handle->bfd_read));
		if(!bfd_set_format(handle, bfd_get_format(file_handle->bfd_read)))
			RETURN(LIBR_ERROR_SETFORMAT, "Failed to set output file format to input file format");
		if(!bfd_set_arch_mach(handle, bfd_get_arch(file_handle->bfd_read), bfd_get_mach(file_handle->bfd_read)))
			RETURN(LIBR_ERROR_SETARCH, "Failed to set output file architecture to input file architecture");
		/* twice needed ? */
		if(!bfd_set_format(handle, bfd_get_format(file_handle->bfd_read)))
			RETURN(LIBR_ERROR_SETFORMAT, "Failed to set output file format to input file format");
		file_handle->bfd_write = handle;
	}
	else
	{
		file_handle->fd_handle = 0;
		file_handle->bfd_write = NULL;
	}
	RETURN_OK;
}

/*
 * Check to see if a symbol should be kept
 */
int keep_symbol(libr_section *sections, libr_section *chkscn)
{
	libr_section *scn;
	
	/* Check that the section is publicly exposed */
	for(scn = sections; scn != NULL; scn = scn->next)
	{
		if(scn == chkscn)
		{
			/* if it is, and has size zero, then it was marked for deletion */
			if(
				#ifdef HAVE_BFD_2_34
				bfd_section_size(chkscn) == 0
				#else
				bfd_get_section_size(chkscn) == 0
				#endif
			)
			{
				return false;
			}
			return true;
		}
	}
	return true;
}

/*
 * Remove the symbol corresponding to a deleted section
 */
void remove_sections(libr_section *sections, void *symtab_buffer, long *symtab_count)
{ 
	asymbol **symtab = (asymbol **) symtab_buffer;
	long i, cnt = *symtab_count;
	
	for(i=0;i<cnt;i++)
	{
		libr_section *chkscn = NULL;
		asymbol *symbol = symtab[i];
		
		if(symbol != NULL)
		{
			#ifdef HAVE_BFD_2_34
			chkscn = bfd_asymbol_section(symbol);
			#else
			chkscn = bfd_get_section(symbol);
			#endif
		}
		if(chkscn != NULL && !keep_symbol(sections, chkscn))
		{
			/* remove the symbol from the table */
			asymbol **tmp = (asymbol **) malloc(sizeof(asymbol *) * (cnt-(i+1)));
			memcpy(&tmp[0], &symtab[i+1], sizeof(asymbol *) * (cnt-(i+1)));
			memcpy(&symtab[i], &tmp[0], sizeof(asymbol *) * (cnt-(i+1)));
			free(tmp);
			cnt--;
		}
	}
	*symtab_count = cnt;
}

int setup_sections(bfd *ihandle, bfd *ohandle)
{
	libr_section *iscn, *oscn;
	bfd_vma vma;
	
	for(iscn = ihandle->sections; iscn != NULL; iscn = iscn->next)
	{
		if(
			#ifdef HAVE_BFD_2_34
			bfd_section_size(iscn) == 0
			#else
			bfd_get_section_size(iscn) == 0
			#endif
		)
		{
			continue; /* Section has been marked for deletion */
		}
		/* Use SEC_LINKER_CREATED to ask the libbfd backend to take care of configuring the section */

		// Keep the ARM_ATTRIBUTES section type intact on armhf systems
		// If this is not done, readelf -A will not print any architecture information for the modified library,
		// and ldd will report that the library cannot be found
		if (strcmp(iscn->name, ".ARM.attributes") == 0)
		{
			oscn = bfd_make_section_anyway_with_flags(ohandle, iscn->name, iscn->flags);
		}
		else
		{
			oscn = bfd_make_section_anyway_with_flags(ohandle, iscn->name, iscn->flags | SEC_LINKER_CREATED);
		}
		if(oscn == NULL)
		{
			printf("failed to create out section: %s\n", bfd_errmsg(bfd_get_error()));
			return false;
		}
		if(
			#ifdef HAVE_BFD_2_34
			!bfd_set_section_size(oscn, iscn->size)
			#else
			!bfd_set_section_size(ohandle, oscn, iscn->size)
			#endif
		)
		{
			printf("failed to set data size: %s\n", bfd_errmsg(bfd_get_error()));
			return false;
		}
		#ifdef HAVE_BFD_2_34
		vma = bfd_section_vma(iscn);
		#else
		vma = bfd_section_vma(ihandle, iscn);
		#endif
		if(
			#ifdef HAVE_BFD_2_34
			!bfd_set_section_vma(oscn, vma)
			#else
			!bfd_set_section_vma(ohandle, oscn, vma)
			#endif
		)
		{
			printf("failed to set virtual memory address: %s\n", bfd_errmsg(bfd_get_error()));
			return false;
		}
		oscn->lma = iscn->lma;
		if(
			#ifdef HAVE_BFD_2_34
			!bfd_set_section_alignment(oscn, bfd_section_alignment(iscn))
			#else
			!bfd_set_section_alignment(ohandle, oscn, bfd_section_alignment(ihandle, iscn))
			#endif
		)
		{
			printf("failed to compute section alignment: %s\n", bfd_errmsg(bfd_get_error()));
			return false;
		}
		oscn->entsize = iscn->entsize;
		iscn->output_section = oscn;
		iscn->output_offset = vma;
		if(!bfd_copy_private_section_data(ihandle, iscn, ohandle, oscn))
		{
			printf("failed to compute section alignment: %s\n", bfd_errmsg(bfd_get_error()));
			return false;
		}
	}
	return true;
}

/*
 * Go through the rather complicated process of using libbfd to build the output file
 */
int build_output(libr_file *file_handle)
{
	void *symtab_buffer = NULL, *reloc_buffer = NULL, *buffer = NULL;
	bfd_size_type symtab_size, reloc_size, size;
	bfd *ohandle = file_handle->bfd_write;
	bfd *ihandle = file_handle->bfd_read;
	long symtab_count, reloc_count;
	libr_section *iscn, *oscn;
	
	if(!bfd_set_start_address(ohandle, bfd_get_start_address(ihandle)))
	{
		printf("failed to set start address: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	if(!bfd_set_file_flags(ohandle, bfd_get_file_flags(ihandle)))
	{
		printf("failed to set file flags: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	/* Setup the sections in the output file */
	if(!setup_sections(ihandle, ohandle))
		return false; /* error already printed */
	if(!bfd_copy_private_header_data(ihandle, ohandle))
	{
		printf("failed to copy header: %s\n", bfd_errmsg(bfd_get_error()));
		return false; /* failed to create section */
	}
	/* Get the old symbol table */
	if((bfd_get_file_flags(ihandle) & HAS_SYMS) == 0)
	{
		printf("file has no symbol table: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	symtab_size = bfd_get_symtab_upper_bound(ihandle);
	if((signed)symtab_size < 0)
	{
		printf("failed to get symbol table size: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	symtab_buffer = malloc(symtab_size);
	symtab_count = bfd_canonicalize_symtab(ihandle, symtab_buffer);
	if(symtab_count < 0)
	{
		printf("failed to get symbol table number of entries: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	/* Tweak the symbol table to remove sections that no-longer exist */
	remove_sections(ihandle->sections, symtab_buffer, &symtab_count);
	bfd_set_symtab(ohandle, symtab_buffer, symtab_count);
	/* Actually copy section data */
	for(iscn = ihandle->sections; iscn != NULL; iscn = iscn->next)
	{
		#ifdef HAVE_BFD_2_34
		size = bfd_section_size(iscn);
		#else
		size = bfd_get_section_size(iscn);
		#endif
		if(size == 0)
			continue; /* Section has been marked for deletion */
		oscn = iscn->output_section;
		reloc_size = bfd_get_reloc_upper_bound(ihandle, iscn);
		if(reloc_size == 0)
			bfd_set_reloc(ohandle, oscn, NULL, 0);
		else
		{
			reloc_buffer = malloc(reloc_size);
			reloc_count = bfd_canonicalize_reloc(ihandle, iscn, reloc_buffer, symtab_buffer);
			bfd_set_reloc(ohandle, oscn, reloc_buffer, reloc_count);
		}

		if(
			#ifdef HAVE_BFD_2_34
			bfd_section_flags(iscn) & SEC_HAS_CONTENTS
			#else
			bfd_get_section_flags(ihandle, iscn) & SEC_HAS_CONTENTS
			#endif
		)
		{
			/* NOTE: if the section is just being copied then do that, otherwise grab
			 * the user data for the section (stored previously by set_data)
			 */
			if(iscn->userdata == NULL)
			{
				buffer = malloc(size);
				if(!bfd_get_section_contents(ihandle, iscn, buffer, 0, size))
				{
					printf("failed to get section contents: %s\n", bfd_errmsg(bfd_get_error()));
					free(buffer);
					return false;
				}
			}
			else
				buffer = iscn->userdata;
			if(!bfd_set_section_contents(ohandle, oscn, buffer, 0, size))
			{
				printf("failed to set section contents: %s\n", bfd_errmsg(bfd_get_error()));
				free(buffer);
				return false;
			}
			free(buffer);
			if(!bfd_copy_private_section_data(ihandle, iscn, ohandle, oscn))
			{
				printf("failed to copy private section data: %s\n", bfd_errmsg(bfd_get_error()));
				return false;
			}
		}
	}
	if(!bfd_copy_private_bfd_data(ihandle, ohandle))
	{
		printf("failed to copy private data: %s\n", bfd_errmsg(bfd_get_error()));
		return false;
	}
	return true;
}

/*
 * Perform a cross-device safe rename
 */
int safe_rename(const char *old, const char *new)
{
	char buffer[1024];
	FILE *in, *out;
	int read;

	in = fopen(old, "r");
	if(!in)
		return -1;
	out = fopen(new, "w");
	if(!out)
		return -1;
	while(!feof(in) && !ferror(in))
	{
		read = fread(buffer, 1, sizeof(buffer), in);
		fwrite(buffer, read, 1, out);
	}
	fclose(in);
	fclose(out);
	if(ferror(in))
	{
		remove(new);
		return -1;
	}
	return remove(old);
}

/*
 * Write the output file using the libbfd method
 */
int write_output(libr_file *file_handle)
{
	int write_ok = false;

	if(file_handle->bfd_write != NULL)
	{
		write_ok = true;
		if(!build_output(file_handle))
		{
			printf("BFD::write_output failed to build output file.\n");
			write_ok = false;
		}
		else
        {
            printf("BFD::write_output built output file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }

		if(!bfd_close(file_handle->bfd_write))
		{
			printf("BFD::write_output failed to close write handle.\n");
			write_ok = false;
		}
		else
        {
            printf ("BFD::write_output closed file handle: file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }

		if(file_handle->fd_handle != 0 && close(file_handle->fd_handle))
		{
			write_ok = false;
			printf("BFD::write_output failed to close write file descriptor file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
		}
		else
        {
            printf ("BFD::write_output closed file descriptor: file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }
	}
	/* The read handle must be closed last since it is used in the write process */
	if(!bfd_close(file_handle->bfd_read))
    {
		printf("BFD::write_output failed to close read handle file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
    }
    else
    {
        printf ("BFD::write_output  closed read handle: file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
    }

    return (write_ok);

	// Copy the temporary output over the input
	/*
	if(write_ok)
	{
		if(rename(file_handle->tempfile, file_handle->filename) < 0)
		{
			if(errno != EXDEV || safe_rename(file_handle->tempfile, file_handle->filename) < 0)
            {
				printf("BFD::write_output failed to rename output file: %m (temp:%s->file:%s)\n", file_handle->tempfile, file_handle->filename);
            }
            else
            {
                printf("BFD::write_output renamed (%s->%s)\n", file_handle->filename, file_handle->tempfile);
            }
		}

		if(chmod(file_handle->filename, file_handle->filemode) < 0)
        {
			printf("BFD::write_output failed to set file mode file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }
        else
        {
            printf("BFD::write_output chmod success file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }

		if(chown(file_handle->filename, file_handle->fileowner, file_handle->filegroup) < 0)
        {
			printf("BFD::write_output failed to set file ownership file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }
        else
        {
            printf("BFD::write_output chown success file: %s temp: %s\n", file_handle->filename, file_handle->tempfile);
        }
	}
	*/
}

/*
 * Find a named section from the ELF file using libbfd
 */
libr_intstatus find_section(libr_file *file_handle, char *section_name, libr_section **retscn)
{
	libr_section *scn;

	for(scn = file_handle->bfd_read->sections; scn != NULL; scn = scn->next)
	{
		if(strcmp(scn->name, section_name) == 0)
		{
			*retscn = scn;
			RETURN_OK;
		}
	}
	RETURN(LIBR_ERROR_NOSECTION, "ELF resource section not found");
}

/*
 * Obtain the data from a section using libbfd
 */
libr_data *get_data(libr_file *file_handle, libr_section *scn)
{
	libr_data *data = malloc(scn->size);

	if(!bfd_get_section_contents(file_handle->bfd_read, scn, data, 0, scn->size))
	{
		free(data);
		data = NULL;
	}
	scn->userdata = data;
	return data;
}

/*
 * Create new data for a section using libbfd
 */
libr_data *new_data(libr_file *file_handle, libr_section *scn)
{
	/* NOTE: expanding data is handled by set_data for libbfd */
	if(scn->userdata != NULL)
		return scn->userdata;
	scn->size = 0;
	scn->userdata = malloc(0);
	return scn->userdata;
}

/*
 * Create new data for a section using libbfd (at least, do so memory-wise)
 */
libr_intstatus set_data(libr_file *file_handle, libr_section *scn, libr_data *data, off_t offset, char *buffer, size_t size)
{
	char *intbuffer = NULL;

	/* special case: clear buffer */
	if(buffer == NULL)
	{
		scn->size = 0;
		if(scn->userdata != NULL)
			free(scn->userdata);
		RETURN_OK;
	}
	/* normal case: add new data to the buffer */
	scn->size = offset + size;
	scn->userdata = realloc(data, scn->size);
	if(scn->userdata == NULL)
		RETURN(LIBR_ERROR_MEMALLOC, "Failed to allocate memory for data");
	intbuffer = scn->userdata;
	memcpy(&intbuffer[offset], buffer, size);
	RETURN_OK;
}

/*
 * Create a new section using libbfd
 */
libr_intstatus add_section(libr_file *file_handle, char *resource_name, libr_section **retscn)
{
	libr_section *scn = NULL;
	
	scn = bfd_make_section(file_handle->bfd_read, resource_name);
	if(scn == NULL)
		RETURN(LIBR_ERROR_NEWSECTION, "Failed to create new section");
	if(
		#ifdef HAVE_BFD_2_34
		!bfd_set_section_flags(scn, SEC_HAS_CONTENTS | SEC_DATA | SEC_IN_MEMORY)
		#else
		!bfd_set_section_flags(file_handle->bfd_read, scn, SEC_HAS_CONTENTS | SEC_DATA | SEC_IN_MEMORY)
		#endif
	)
	{
		RETURN(LIBR_ERROR_SETFLAGS, "Failed to set flags for section");
	}
	*retscn = scn;
	RETURN_OK;
}

/*
 * Remove a section and eliminate it from the ELF string table using libbfd
 */
libr_intstatus remove_section(libr_file *file_handle, libr_section *scn)
{
	scn->size = 0;
	RETURN_OK;
}

/*
 * Return the pointer to the actual data in the section
 */
void *data_pointer(libr_section *scn, libr_data *data)
{
	return data;
}

/*
 * Return the size of the data in the section
 */
size_t data_size(libr_section *scn, libr_data *data)
{
	return scn->size;
}

/*
 * Return the next section in the ELF file
 */
libr_section *next_section(libr_file *file_handle, libr_section *scn)
{
	/* get the first section */
	if(scn == NULL)
	{
		if(file_handle->bfd_read == NULL)
			return NULL;
		return file_handle->bfd_read->sections;
	}
	return scn->next;
}

/*
 * Return the name of a section
 */
char *section_name(libr_file *file_handle, libr_section *scn)
{
	return (char *) scn->name;
}

/*
 * Initialize libbfd
 */
void initialize_backend(void)
{
	bfd_init();
}

#endif
