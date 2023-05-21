#!/bin/bash

if [ ! -f /var/lib/mysql/mysql ]; then

	# touch /var/lib/mysql/mysql.sock
	chown -R mysql:mysql /var/lib/mysql
fi

service mysql start;
sleep 2;
mysql -u root -e "FLUSH PRIVILEGES;"
mysql -u root -e "CREATE DATABASE ${SQL_DATABASE};"
mysql -u root -e "CREATE USER '${SQL_USER}'@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mysql -u root -e "GRANT ALL PRIVILEGES ON ${SQL_DATABASE}.* TO '${SQL_USER}'@'%';"
mysql -u root -e "FLUSH PRIVILEGES;"
mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
mysqladmin -u root -p${SQL_ROOT_PASSWORD} shutdown

exec mysqld_safe
