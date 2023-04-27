#!/bin/bash

if [ ! -d "/var/lib/mysql/mysql" ]; then
	touch /var/lib/mysql/mysql.sock
	chown -R mysql:mysql /var/lib/mysql
fi

echo $SQL_USER > /var/lib/mysql/log.txt

service mysql start;
mysql -e "CREATE USER IF NOT EXISTS \`${SQL_USER}\`@'localhost' IDENTIFIED BY '${SQL_PASSWORD}';"
mysql -e "GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO \`${SQL_USER}\`@'%' IDENTIFIED BY '${SQL_PASSWORD}';"
mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${SQL_ROOT_PASSWORD}';"
mysql -e "FLUSH PRIVILEGES;"
mysqladmin -u root -p $SQL_ROOT_PASSWORD shutdown
exec mysqld_safe
