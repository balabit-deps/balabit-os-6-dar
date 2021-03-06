if BSD_SED
  SED_REGEX = -E
else
  SED_REGEX = -r
endif

if PROFILING
  LD_PROF = -pg
  CPP_PROF = -pg
clean-local:
	rm -f gmon.out
	rm -f libdar.pc
else
  LD_PROF =
  CPP_PROF =
clean-local:
	rm -f libdar.pc
endif

localedir = @localedir@
pkgconfigdir = @pkgconfigdir@

if BUILD_MODE32
  MYLIB=libdar32.la
  AM_CPPFLAGS=-DLIBDAR_MODE=32 -DDAR_LOCALEDIR=\"$(localedir)\" $(CPP_PROF) $(GPGME_CFLAGS)
  VER_SRC=limitint.o
  LIBDAR_SUFFIX=32
  LIBDAR_MODE=-DLIBDAR_MODE=32
else
if BUILD_MODE64
    MYLIB=libdar64.la
    AM_CPPFLAGS=-DLIBDAR_MODE=64 -DDAR_LOCALEDIR=\"$(localedir)\" $(CPP_PROF) $(GPGME_CFLAGS)
    VER_SRC=limitint.o
    LIBDAR_SUFFIX=64
    LIBDAR_MODE=-DLIBDAR_MODE=64
else
    MYLIB=libdar.la
    AM_CPPFLAGS= -DDAR_LOCALEDIR=\"$(localedir)\" $(CPP_PROF) $(GPGME_CFLAGS)
    VER_SRC=real_infinint.o
    LIBDAR_SUFFIX=
    LIBDAR_MODE=
endif
endif

if WITH_LIBTHREADAR
    LIBTHREADAR_DEP_MODULES=generic_thread.cpp slave_thread.cpp messaging.cpp
else
    LIBTHREADAR_DEP_MODULES=
endif

AM_LDFLAGS = @LTLIBINTL@  $(LD_PROF)
LDADD = $(GPGME_LIBS)
lib_LTLIBRARIES = $(MYLIB)
CXXSTDFLAGS = @CXXSTDFLAGS@

LIBDAR_MAJOR=`grep LIBDAR_COMPILE_TIME_MAJOR libdar.hpp | cut -f 2 -d "=" | cut -f 1 -d ';' | sed -e 's% %%g'`
LIBDAR_MEDIUM=`grep LIBDAR_COMPILE_TIME_MEDIUM libdar.hpp | cut -f 2 -d "=" | cut -f 1 -d ';' | sed -e 's% %%g'`
LIBDAR_MEDIUM_000=`grep LIBDAR_COMPILE_TIME_MEDIUM libdar.hpp | cut -f 2 -d "=" | cut -f 1 -d ';' | sed $(SED_REGEX) -e 's% %%g' -e 's%([^0-9]|^)([0-9]{1})([^0-9]|$$)%0\2%' -e 's%([^0-9]|^)([0-9]{2})([^0-9]|$$)%0\2%'`
LIBDAR_MINOR=`grep LIBDAR_COMPILE_TIME_MINOR libdar.hpp | cut -f 2 -d "=" | cut -f 1 -d ';' | sed -e 's% %%g'`
LIBDAR_LIBTOOL_CURRENT=$(LIBDAR_MAJOR)$(LIBDAR_MEDIUM_000)
LIBDAR_LIBTOOL_REVISION=$(LIBDAR_MINOR)
LIBDAR_LIBTOOL_AGE=$(LIBDAR_MEDIUM)
LIBDAR_VERSION_IN=$(LIBDAR_LIBTOOL_CURRENT):$(LIBDAR_LIBTOOL_REVISION):$(LIBDAR_LIBTOOL_AGE)
LIBDAR_VERSION_OUT=$(LIBDAR_MAJOR).$(LIBDAR_MEDIUM).$(LIBDAR_MINOR)

# header files required by external applications and that must be installed (make install)
dist_noinst_DATA = libdar.hpp path.hpp mask.hpp integers.hpp real_infinint.hpp statistics.hpp user_interaction.hpp erreurs.hpp deci.hpp limitint.hpp infinint.hpp compressor.hpp generic_file.hpp wrapperlib.hpp storage.hpp tuyau.hpp tools.hpp catalogue.hpp cat_entree.hpp cat_nomme.hpp cat_directory.hpp cat_inode.hpp scrambler.hpp archive.hpp header_version.hpp ea.hpp crypto.hpp int_tools.hpp thread_cancellation.hpp tronconneuse.hpp mask_list.hpp database.hpp data_tree.hpp criterium.hpp trontextual.hpp archive_options.hpp user_group_bases.hpp database_options.hpp label.hpp tlv_list.hpp tlv.hpp memory_file.hpp pile.hpp archive_version.hpp mem_ui.hpp fichier_global.hpp fichier_local.hpp erreurs_ext.hpp secu_string.hpp crc.hpp hash_fichier.hpp escape.hpp escape_catalogue.hpp compile_time_features.hpp nls_swap.hpp entrepot.hpp entrepot_local.hpp etage.hpp list_entry.hpp fsa_family.hpp capabilities.hpp on_pool.hpp mem_allocator.hpp memory_pool.hpp datetime.hpp crypto_asym.hpp generic_file_overlay_for_gpgme.hpp secu_memory_file.hpp crypto_sym.hpp mem_sized.hpp mem_cluster.hpp filesystem_specific_attribute.hpp range.hpp pile_descriptor.hpp slice_layout.hpp


install-data-local:
	mkdir -p $(DESTDIR)$(pkgincludedir)
	cp ../../config.h $(DESTDIR)$(pkgincludedir)/libdar_config.h
	sed -e 's%../config.h%libdar_config.h%g' -e 's%HAVE_CONFIG_H%1%g' -e 's%MY_CONFIG_H%LIBDAR_MY_CONFIG_H%g' ../my_config.h  > ./libdar_my_config.h
	cp ../gettext.h .
	for file in $(dist_noinst_DATA) gettext.h libdar_my_config.h ; do sed -e 's%#include \"../my_config.h\"%INC_MY_CONFIG_FILE_H%g' -e "s%#include \"%#include \"$(pkgincludedir)/%g" -e "s%INC_MY_CONFIG_FILE_H%#include \"$(pkgincludedir)/libdar_my_config.h\"%g" "$$file" > $(DESTDIR)$(pkgincludedir)/"$$file"  ; done
	rm libdar_my_config.h gettext.h
	for file in $(DESTDIR)$(pkgincludedir)/* ; do sed -e 's%HAVE_%LIBDAR_HAS_%g' -e 's%PACKAGE%DAR_PACKAGE%g' -e 's%SIZEOF_%LIBDAR_SIZEOF_%g' -e 's%LSTAT_FOLLOWS_SLASHED_SYMLINK%LIBDAR_LSTAT_FOLLOWS_SLASHED_SYMLINK%g' -e 's%VERSION%LIBDAR_VERSION%g' -e 's%MUTEX_WORKS%LIBDAR_MUTEX_WORKS%g' -e 's%OS_BITS%LIBDAR_OS_BITS%g' -e 's%_AVAILABLE%_AVAILABLE_FOR_LIBDAR%g' -e 's%STDC_HEADERS%LIBDAR_STDC_HEADERS%g' -e 's%ENABLE_NLS%DAR_ENABLE_NLS%g' -e 's%HAVE_GETTEXT%DAR_HAS_GETTEXT%g' "$$file" > "$$file.tmp" && mv "$$file.tmp" "$$file" ; done
	egrep 'LIBDAR|DAR_' $(DESTDIR)$(pkgincludedir)/libdar_config.h | grep -v "#undef" >  $(DESTDIR)$(pkgincludedir)/config.h.tmp
	mv  $(DESTDIR)$(pkgincludedir)/config.h.tmp  $(DESTDIR)$(pkgincludedir)/libdar_config.h
	chmod 0644 $(DESTDIR)$(pkgincludedir)/*
	$(INSTALL) -d $(DESTDIR)$(pkgconfigdir)
	$(INSTALL) -m 0644 libdar.pc $(DESTDIR)$(pkgconfigdir)/libdar$(LIBDAR_SUFFIX).pc

uninstall-local:
	rm -rf $(DESTDIR)$(pkgincludedir) $(DESTDIR)$(pkgconfigdir)/libdar$(LIBDAR_SUFFIX).pc

all-local : libdar.pc

libdar.pc : libdar.pc.tmpl
	sed -e "s%#LIBDAR_VERSION#%$(LIBDAR_VERSION_OUT)%g" -e "s%#LIBDAR_SUFFIX#%$(LIBDAR_SUFFIX)%g" -e "s%#LIBDAR_MODE#%$(LIBDAR_MODE)%g" -e "s%#CXXFLAGS#%$(CXXFLAGS)%g" -e "s%#CXXSTDFLAGS#%$(CXXSTDFLAGS)%g" libdar.pc.tmpl > libdar.pc

# header files that are internal to libdar and that must not be installed (make install)
noinst_HEADERS = defile.hpp ea_filesystem.hpp filesystem.hpp filtre.hpp header.hpp macro_tools.hpp null_file.hpp sar.hpp trivial_sar.hpp sar_tools.hpp terminateur.hpp tronc.hpp zapette.hpp cygwin_adapt.hpp elastic.hpp database_header.hpp sparse_file.hpp semaphore.hpp memory_check.hpp messaging.hpp slave_thread.hpp generic_thread.hpp cat_blockdev.hpp cat_chardev.hpp cat_detruit.hpp cat_device.hpp cat_door.hpp cat_eod.hpp cat_file.hpp cat_ignored.hpp cat_ignored_dir.hpp cat_lien.hpp cat_mirage.hpp cat_prise.hpp cat_tube.hpp cat_etoile.hpp cat_all_entrees.hpp cat_tools.hpp generic_to_global_file.hpp

ALL_SOURCES = catalogue.cpp catalogue.hpp compressor.cpp compressor.hpp deci.cpp deci.hpp defile.cpp defile.hpp ea.cpp ea.hpp ea_filesystem.cpp ea_filesystem.hpp erreurs.cpp erreurs.hpp etage.cpp etage.hpp filesystem.cpp filesystem.hpp filtre.cpp filtre.hpp generic_file.cpp generic_file.hpp header.cpp header_version.cpp libdar.cpp macro_tools.cpp mask.cpp path.cpp sar.cpp trivial_sar.cpp sar_tools.cpp scrambler.cpp storage.cpp terminateur.cpp tools.cpp tronc.cpp tuyau.cpp user_interaction.cpp wrapperlib.cpp zapette.cpp archive.cpp crypto.cpp cache.cpp cache.hpp int_tools.cpp tronconneuse.cpp elastic.cpp thread_cancellation.cpp mask_list.cpp database.cpp database_header.cpp data_tree.cpp statistics.cpp criterium.cpp memory_file.cpp tlv.cpp tlv_list.cpp label.cpp trontextual.cpp archive_options.cpp user_group_bases.cpp escape.cpp escape_catalogue.cpp pile.cpp sparse_file.cpp crc.cpp archive_version.cpp mem_ui.cpp fichier_global.cpp fichier_local.cpp hash_fichier.cpp secu_string.cpp semaphore.cpp integers.cpp compile_time_features.cpp memory_check.cpp entrepot.cpp entrepot_local.cpp list_entry.cpp filesystem_specific_attribute.cpp fsa_family.cpp capabilities.cpp on_pool.cpp mem_cluster.cpp mem_sized.cpp mem_allocator.cpp memory_pool.cpp datetime.cpp crypto_asym.cpp generic_file_overlay_for_gpgme.cpp secu_memory_file.cpp crypto_sym.cpp range.cpp slice_layout.cpp cat_detruit.cpp cat_device.cpp cat_directory.cpp cat_door.cpp cat_entree.cpp cat_etoile.cpp cat_file.cpp cat_ignored_dir.cpp cat_inode.cpp cat_lien.cpp cat_mirage.cpp cat_nomme.cpp cat_tools.cpp pile_descriptor.cpp cat_chardev.cpp cat_blockdev.cpp cat_tube.cpp cat_ignored.cpp cat_prise.cpp erreurs_ext.cpp

libdar_la_LDFLAGS = -version-info $(LIBDAR_VERSION_IN)
libdar_la_SOURCES = $(ALL_SOURCES) real_infinint.cpp $(LIBTHREADAR_DEP_MODULES)

libdar32_la_LDFLAGS = -version-info $(LIBDAR_VERSION_IN)
libdar32_la_SOURCES = $(ALL_SOURCES) limitint.cpp $(LIBTHREADAR_DEP_MODULES)

libdar64_la_LDFLAGS = -version-info $(LIBDAR_VERSION_IN)
libdar64_la_SOURCES = $(ALL_SOURCES) limitint.cpp $(LIBTHREADAR_DEP_MODULES)

