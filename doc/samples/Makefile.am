NO_EXE_SAMPLES = darrc_sample sample1.txt  README automatic_backup.txt JH-readme.txt JH_dar_archiver.options JH_darrc cluster_digital_readme.txt index.html PN_backup-root.options PN_backup-storage.options Patrick_Nagel_Note.txt
EXE_SAMPLES = cdbackup.sh pause_every_n_slice.duc automatic_backup dar_backup dar_rqck.bash JH-dar-make_user_backup.sh cluster_digital_backups.sh dar_par_create.duc dar_par_test.duc MyBackup.sh.tar.gz PN_backup-root.sh PN_backup-storage.sh PN_ftpbackup.sh dar_backups.sh available_space.duc
dist_noinst_DATA = $(NO_EXE_SAMPLES) $(EXE_SAMPLES) dar_par.dcf etc_darrc


install-data-hook:
	$(INSTALL) -d $(DESTDIR)$(pkgdatadir)/samples
	sed -e "s%SOMEPATH%$(pkgdatadir)/samples%g" dar_par.dcf > $(DESTDIR)$(pkgdatadir)/samples/dar_par.dcf
	chmod 0644 $(DESTDIR)$(pkgdatadir)/samples/dar_par.dcf
	$(INSTALL) -m 0644 $(NO_EXE_SAMPLES) $(DESTDIR)$(pkgdatadir)/samples
	$(INSTALL) -m 0755 $(EXE_SAMPLES) $(DESTDIR)$(pkgdatadir)/samples
	$(INSTALL) -d $(DESTDIR)$(sysconfdir)
	sed -e "s%SOMEPATH%$(pkgdatadir)/samples%g" etc_darrc > $(DESTDIR)$(sysconfdir)/darrc

uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir)/samples

# $(sysconfdir)/darrc not removed as it may contain system admin specific configuration

