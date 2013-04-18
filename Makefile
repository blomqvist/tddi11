LABS = hello_world lab1 lab2 lab3 lab4 lab5

help:
	@echo "Please select one rule: "
	@echo "  gmake clean"
	@echo "  gmake all"

all: check
	@for lab in $(LABS) ; do \
	   gmake -C $$lab ; \
	done

clean: check
	@for lab in $(LABS) ; do \
	   gmake -C $$lab clean ; \
	done

check:
#	Test that GNU make 3.x are running
	@echo $(MAKE_VERSION) | grep '3\.' > /dev/null \
	|| (printf "\n >>> ERROR: Please use gmake, not make <<< \n\n" \
	&& /bin/false)
#	Test that the course module is loaded
#	( Adding the module command here could be dangerous (?) )
	@/sw/modules/bin/modulecmd sh list 2>&1 | grep tddi11 > /dev/null \
	|| (printf "Please run: \"module add $(COURSE)/modulefiles/tddi11\"\n" \
	&& /bin/false)
