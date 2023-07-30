FROM php:8.1-apache

RUN apt-get update
RUN apt-get install -y libzip-dev
RUN docker-php-ext-install zip

#Install git and MySQL extensions for PHP
RUN docker-php-ext-install bcmath mysqli pdo pdo_mysql && docker-php-ext-enable pdo_mysql
COPY --from=composer:latest /usr/bin/composer /usr/local/bin/composer


#RUN docker-php-ext-install pdo pdo_mysql mysqli bcmath mbstring xml curl

#RUN update-alternatives --set php /usr/bin/php8.1
#RUN a2enmod rewrite

COPY www /var/www/html/
EXPOSE 80/tcp
EXPOSE 443/tcp
EXPOSE 8000