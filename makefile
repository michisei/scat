CC=gcc
CFLAGS= -g -Wall -Wpedantic 

exec_out=bin/scat

LD=gcc
LDFLAGS= 
LDLIBS=

sources := src/options.c src/os_utils.c src/slow_cat.c
obj_files := $(patsubst src/%.c,obj/%.o,$(sources))

all: bin obj $(exec_out)

$(exec_out): $(obj_files)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir $@

bin:
	mkdir $@

clean_obj/%.o:
	-rm $(patsubst clean_%,%,$@)

clean_obj: $(patsubst obj/%.o,clean_obj/%.o,$(obj_files))
	-rm -d $(patsubst clean_%,%,$@)

clean_$(exec_out):
	-rm $(exec_out)

clean_bin: clean_$(exec_out)
	-rm -d $(patsubst clean_%,%,$@)

clean: clean_bin clean_obj
