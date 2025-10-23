name=rand

directory_include=include
directory_library=library
directory_objects=objects
directory_objects_executable=${directory_objects}/executable
directory_output=output
directory_sources=sources
directory_sources_executable=${directory_sources}/executable

ifndef directory_clic3
	directory_clic3=../clic3
endif
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library

file_object_entry_point=${directory_objects_executable}/${name}_executable.o
file_output=${directory_output}/${name}
file_library=${directory_library}/${name}.o

file_clic3_library=${directory_clic3_library}/clic3.o

files_sources_executable=${wildcard ${directory_sources_executable}/*.c}
files_sources_library=${wildcard ${directory_sources}/*.c}

files_objects_executable=${patsubst ${directory_sources_executable}/%.c, ${directory_objects_executable}/%.o, ${files_sources_executable}}
files_objects_library=${patsubst ${directory_sources}/%.c, ${directory_objects}/%.o, ${files_sources_library}}

cc=gcc
c_flags=-O3 -I${directory_include} -I${directory_clic3_include}

ld=ld
l_flags=

all: library rand

rand: ${file_output}

library: ${file_library}

${file_library}: ${files_objects_library}
	mkdir -p ${directory_library}
	${ld} ${l_flags} -r ${files_objects_library} ${file_clic3_library} -o ${file_library}

${file_output}: ${files_objects_library} ${files_objects_executable}	
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${files_objects_library} ${files_objects_executable} ${file_clic3_library} -o ${file_output}

${directory_objects_executable}/%.o: ${directory_sources_executable}/%.c	
	mkdir -p ${directory_objects_executable}
	${cc} ${c_flags} -c $< -o $@

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

clean: clean_library clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_output:
	-rm -r ${directory_output} 2> /dev/null

clean_library:
	-rm -r ${directory_library} 2> /dev/null
