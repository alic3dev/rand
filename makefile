name=rand

directory_include=include
directory_library=library
directory_objects=objects
directory_objects_executable=${directory_objects}/executable
directory_output=output
directory_sources=sources
directory_sources_executable=${directory_sources}/executable

file_object_entry_point=${directory_objects_executable}/${name}_executable.o
file_output=${directory_output}/${name}
file_library=${directory_library}/${name}.o

files_sources_executable=${wildcard ${directory_sources_executable}/*.c}
files_sources_library=${wildcard ${directory_sources}/*.c}

files_objects_executable=${patsubst ${directory_sources_executable}/%.c, ${directory_objects_executable}/%.o, ${files_sources_executable}}
files_objects_library=${patsubst ${directory_sources}/%.c, ${directory_objects}/%.o, ${files_sources_library}}

symbol_entry_point_origin=${name}_executable

ifeq (${shell which objcopy},)
	objcp=:
	symbol_entry_point_origin:=_${symbol_entry_point_origin}
	symbol_entry_point=${symbol_entry_point_origin}
else
	objcp=objcopy
	symbol_entry_point=main
endif

cc=gcc
c_flags=-O3 -I${directory_include}

ld=ld
l_flags=

all: library rand

rand: ${file_output}

library: ${file_library}

${file_library}: ${files_objects_library}
	mkdir -p ${directory_library}
	${ld} ${l_flags} -r ${files_objects_library} -o ${file_library}

${file_output}: ${files_objects_library} ${files_objects_executable}	
	${objcp} --redefine-sym ${symbol_entry_point_origin}=${symbol_entry_point} ${file_object_entry_point} ${file_object_entry_point}
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${files_objects_library} ${files_objects_executable} -e ${symbol_entry_point} -o ${file_output}

${directory_objects_executable}/%.o: ${directory_sources_executable}/%.c	
	mkdir -p ${directory_objects_executable}
	${cc} ${c_flags} -c $< -o $@

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

clean: clean_library clean_output clean_objects

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_output:
	-rm -r ${directory_output} 2> /dev/null

clean_library:
	-rm -r ${directory_library} 2> /dev/null

