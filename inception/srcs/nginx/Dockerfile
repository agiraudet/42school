FROM	debian:buster

LABEL	maintainer="agiraude <agiraude@student.42.fr>"
LABEL	description="Nginx"

RUN		apt-get update && apt-get install -y nginx openssl && \
		mkdir -p /var/www/demo && \
		chown -R www-data:www-data /var/www/demo

COPY	conf/nginx.conf /etc/nginx/sites-available/demo

RUN		ln -s /etc/nginx/sites-available/demo /etc/nginx/sites-enabled/ && \
		rm -f /etc/nginx/sites-enabled/default && \
		openssl req -x509 -nodes -days 365 \
		-subj "/C=FR/ST=IdF/L=PARIS/O=42/OU=STUDENT/CN=agiraude" \
		-newkey rsa:4096 \
		-keyout /etc/ssl/private/demo.key \
		-out /etc/ssl/certs/demo.crt

EXPOSE	443

CMD	["nginx", "-g", "daemon off;"]
