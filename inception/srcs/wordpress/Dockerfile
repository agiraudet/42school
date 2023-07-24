FROM	debian:buster

LABEL	maintainer="agiraude <agiraude@student.42.fr>"
LABEL	description="WordPress"

RUN		apt-get update && apt-get install -y \
		wget \
		curl \
		php7.3 \
		php7.3-mysql \
		php-fpm \
		mariadb-client

EXPOSE	9000

ARG		MYSQL_ROOT_PASSWORD
ARG		MYSQL_PASSWORD
ARG		MYSQL_USER
ARG		DB_NAME
ARG		MYSQL_HOST
ARG		DOMAIN_NAME
ARG		WP_ADMIN
ARG		WP_ADMIN_PASSWORD
ARG		WP_USER
ARG		WP_PASSWORD


COPY	conf/www.conf /etc/php/7.3/fpm/pool.d
COPY	tools/setup.sh /setup.sh

RUN		mkdir /run/php/ && \
		chmod +x /setup.sh

RUN		wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
		chmod +x wp-cli.phar && \
		cp wp-cli.phar /usr/local/bin/wp && \
		mkdir -p /var/www/wordpress

WORKDIR	/var/www/wordpress

CMD [ "sh", "/setup.sh" ]
