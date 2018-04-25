# UTD CS3377 CDK 
# Ronak Hegde
# rph160130@utdallas.edu

CXX = g++
CXXFLAGS = -Wall -g
CPPFLAGS = -I/people/cs/s/sxp127930/include
LDFLAGS = -L/people/cs/s/sxp127930/lib
LDLIBS = -lcdk -lcurses 



# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = CS3377.HW6

EXECFILE = cdkProgram

OBJS = mainFile.o

all: $(EXECFILE)

#this is the clean target
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

#we create the executable using the object files from depencies 
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

