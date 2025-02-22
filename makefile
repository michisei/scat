CC=javac

exec_out=bin/scat.jar

LD=jar 
LDFLAGS= cfe 

sources   := src/SlowCat/SlowCat.java src/SlowCat/Options.java
obj_files := build/SlowCat/SlowCat.class build/SlowCat/Options.class

all: bin $(exec_out)

$(exec_out): $(obj_files)
	$(LD) $(LDFLAGS) $@ $(patsubst build/%.class,%,$<) $(patsubst build/%.class,-C build %.class,$^)

build/SlowCat/%.class: src/SlowCat/%.java build/SlowCat
	$(CC) -cp src -d build $<

build/SlowCat: build
	if [ ! -d '$@' ]; \
	then              \
	    mkdir $@;     \
	fi                \

build:
	if [ ! -d '$@' ]; \
	then              \
	    mkdir $@;     \
	fi                \

bin:
	mkdir $@

clean_build/%.class:
	-if [ -f "$(patsubst clean_%,%,$@)" ]; \
	then                                   \
	    rm -v "$(patsubst clean_%,%,$@)";  \
	fi                                     \

clean_build/SlowCat: 
	-rm -d $(patsubst clean_%,%,$@)

clean_build: $(patsubst build/%.class,clean_build/%.class,$(obj_files)) clean_build/SlowCat
	-rm -d $(patsubst clean_%,%,$@)

clean_$(exec_out):
	-if [ -f "$(patsubst clean_%,%,$@)" ]; \
	then                                   \
	    rm -v "$(patsubst clean_%,%,$@)";  \
	fi                                     \

clean_bin: clean_$(exec_out)
	-rm -d $(patsubst clean_%,%,$@)

clean: clean_bin clean_build
