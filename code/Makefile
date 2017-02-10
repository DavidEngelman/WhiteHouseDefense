## -*- Makefile -*-
##
## User: greg
## Time: Feb 10, 2017 2:46:52 PM
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


all: $(TARGETDIR_server)/server

## Target: server
OBJS_server = 
SYSLIBS_server = -lpthread -lcurses 
USERLIBS_server = $(SYSLIBS_server) 
DEPLIBS_server =  
LDLIBS_server = $(USERLIBS_server)


# Link or archive
$(TARGETDIR_server)/server: $(TARGETDIR_server) $(OBJS_server) $(DEPLIBS_server)
	$(LINK.c) $(CFLAGS_server) $(CPPFLAGS_server) -o $@ $(OBJS_server) $(LDLIBS_server)


# Compile source files into .o files


#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_server)/server
	rm -f -r $(TARGETDIR_server)


# Create the target directory (if needed)
$(TARGETDIR_server):
	mkdir -p $(TARGETDIR_server)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

