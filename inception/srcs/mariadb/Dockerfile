FROM	debian:buster

LABEL	maintainer="agiraude <agiraude@student.42.fr>"
LABEL	description="MariaDB Server"

RUN		apt-get update && apt-get install -y mariadb-server

EXPOSE	3306

ARG		MYSQL_ROOT_PASSWORD
ARG		MYSQL_PASSWORD
ARG		MYSQL_USER
ARG		DB_NAME

COPY	conf/db_install.sql /db.sql

RUN		sed -i "s/MYSQL_USER/$MYSQL_USER/g" /db.sql && \
		sed -i "s/DB_NAME/$DB_NAME/g" /db.sql && \
		sed -i "s/MYSQL_PASSWORD/$MYSQL_PASSWORD/g" /db.sql && \
		sed -i "s/MYSQL_ROOT_PASSWORD/$MYSQL_ROOT_PASSWORD/g" /db.sql && \
		sed -i "s/127.0.0.1/0.0.0.0/g" /etc/mysql/mariadb.conf.d/50-server.cnf

RUN		service mysql start && \
		mysql -sfu root < /db.sql

HEALTHCHECK	--start-period=20s CMD mysqladmin ping --silent

CMD ["mysqld"]
