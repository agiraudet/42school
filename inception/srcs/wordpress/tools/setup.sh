#!/bin/bash

wp core download --allow-root
wp core config --dbname="$DB_NAME" --dbuser="$MYSQL_USER" --dbpass="$MYSQL_PASSWORD" --dbhost="$MYSQL_HOST":"3306" --allow-root
chmod 644 wp-config.php
wp core install --url="$DOMAIN_NAME" --title="Hello Inception" --admin_user="$WP_ADMIN" --admin_password="$WP_ADMIN_PASSWORD" --admin_email="agiraude@student.42.fr" --allow-root
wp user create $WP_USER agwp@randomuser.com --role='subscriber' --user_pass="$WP_PASSWORD" --allow-root
wp option update comment_registration 1 --allow-root
exec /usr/sbin/php-fpm7.3 -F
