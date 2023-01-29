#
# Regular cron jobs for the ctrlr package
#
0 4	* * *	root	[ -x /usr/bin/ctrlr_maintenance ] && /usr/bin/ctrlr_maintenance
