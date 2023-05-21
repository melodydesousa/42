#!/bin/bash
sleep 10
cd /var/www/wordpress/
if [ ! -f '/var/www/wordpress/wp-config.php' ]
then
	wp config create --allow-root --dbname=$SQL_DATABASE --dbuser=$SQL_USER --dbpass=$SQL_PASSWORD --dbhost=$MDB_HOST --path='/var/www/wordpress'
	wp core install --url=$WP_URL --title=$WP_TITLE --admin_user=$ADMIN_USER --admin_email=$ADMIN_EMAIL --skip-email --admin_password=$ADMIN_PASS --allow-root
	wp user create $USERWP $USER_EMAIL --role=author --user_pass=$USER_PASS --allow-root
fi
php-fpm7.3 -F