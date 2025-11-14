name=rand

version_major=0
version_minor=1
version_patch=0
version_major_minor=${version_major}.${version_minor}
version=${version_major}.${version_minor}.${version_patch}

directory_objects_base=objects
directory_objects_executable_base=objects/executable
directory_library=library
directory_library_debug=${directory_library}_debug

directory_objects=${directory_objects_base}/release
directory_objects_executable=${directory_objects_executable_base}/release


ifndef directory_clic3
	directory_clic3=../clic3
endif
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library

file_output=${directory_output}/${name}

file_clic3_library=${directory_clic3_library}/clic3.0.dylib

ifeq (${debug}, 1)
	name:=${name}_debug
	directory_objects=${directory_objects_base}/debug
	directory_objects_executable=${directory_objects_executable_base}/debug
	directory_library:=${directory_library_debug}
	directory_clic3_library=${directory_clic3}/library_debug
	file_clic3_library=${directory_clic3_library}/clic3_debug.0.dylib
endif

directory_include=include
directory_output=output
directory_sources=sources
directory_sources_executable=${directory_sources}/executable

files_sources_executable=${wildcard ${directory_sources_executable}/*.c}
files_sources_library=${wildcard ${directory_sources}/*.c}

files_objects_executable=${patsubst ${directory_sources_executable}/%.c, ${directory_objects_executable}/%.o, ${files_sources_executable}}
files_objects_library=${patsubst ${directory_sources}/%.c, ${directory_objects}/%.o, ${files_sources_library}}

files_dylibs=${file_clic3_library}

cc=gcc
c_flags=-I${directory_include} -I${directory_clic3_include}

ifeq (${debug}, 1)
	c_flags:=${c_flags} -O0 -g -v -da -Q
else
	c_flags:=${c_flags} -O3
endif

ar=ar
ar_flags=cqS

ld=ld
ld_flags=

strip=strip
strip_flags=-x

file_library_object=${directory_library}/${name}.o

name_library_dylib_major=${name}.${version_major}.dylib
file_library_dylib=${directory_library}/${name}.dylib
file_library_dylib_major=${directory_library}/${name_library_dylib_major}

name_library_dynamic_major=${name}.${version_major}.so
file_library_dynamic=${directory_library}/${name}.so
file_library_dynamic_major=${directory_library}/${name_library_dynamic_major}

file_library_static=${directory_library}/${name}.a

all: library ${name}

${name}_dylib: ${file_library_dylib}
${name}_dynamic: ${file_library_dynamic}
${name}_object: ${file_library_object}
${name}_static: ${file_library_static}

${name}: ${file_output}

library: ${file_library_dylib} ${file_library_dynamic} ${file_library_object} ${file_library_static}

run: ${file_output}
	cd ${directory_output} && ./${shell basename ${file_output}}

${file_library_dylib}: ${files_objects_library}
	mkdir -p ${directory_library}
	${cc} -dynamiclib -install_name ${name_library_dylib_major} -current_version ${version} -compatibility_version ${version_major_minor} ${files_dylibs} ${files_objects_library} -o ${file_library_dylib_major}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_dylib_major}
endif
	-rm ${file_library_dylib}
	ln -s ${name_library_dylib_major} ${file_library_dylib}

${file_library_dynamic}: ${files_objects_library}
	mkdir -p ${directory_library}
	${cc} -shared -install_name ${name_library_dynamic_major} -current_version ${version} -compatibility_version ${version_major_minor} ${files_dylibs} ${files_objects_library} -o ${file_library_dynamic_major}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_dynamic_major}
endif
	-rm ${file_library_dynamic}
	ln -s ${name_library_dynamic_major} ${file_library_dynamic}

${file_library_object}: ${files_objects_library}
	mkdir -p ${directory_library}
	${ld} ${ld_flags} -r ${files_objects_library} -o ${file_library_object}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_object}
endif

${file_library_static}: ${files_objects_library}
	mkdir -p ${directory_library}
	${ar} ${ar_flags} ${file_library_static} ${files_objects_library}

${file_output}: ${files_objects_library} ${files_objects_executable}	
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${files_dylibs} ${files_objects_library} ${files_objects_executable} ${file_clic3_library} -o ${file_output}
	-rm ${directory_output}/${shell basename ${file_clic3_library}}
	ln -s ${file_clic3_library} ${directory_output}/${shell basename ${file_clic3_library}}

${directory_objects_executable}/%.o: ${directory_sources_executable}/%.c	
	mkdir -p ${directory_objects_executable}
	${cc} ${c_flags} -c $< -o $@

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

clean: clean_library clean_library_debug clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_output:
	-rm -r ${directory_output} 2> /dev/null

clean_library:
	-rm -r ${directory_library} 2> /dev/null

clean_library_debug:
	-rm -r ${directory_library_debug} 2> /dev/null
