CREATE TABLE `classes` (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `name` varchar(255) NOT NULL,
 `info` text,
 `teacherid` int(11) NOT NULL,
 PRIMARY KEY (`id`)
);

CREATE TABLE `forums` (
 `id` int(255) NOT NULL AUTO_INCREMENT,
 `classid` int(11) NOT NULL,
 `userid` int(11) NOT NULL,
 `content` text NOT NULL,
 `date` datetime NOT NULL,
 PRIMARY KEY (`id`)
);

CREATE TABLE `logins` (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `username` varchar(40) NOT NULL,
 `password` varchar(255) NOT NULL,
 `access` int(1) NOT NULL,
 `email` varchar(255) NOT NULL,
 `name` text NOT NULL,
 `surname` text NOT NULL,
 `phone` varchar(40) NOT NULL,
 PRIMARY KEY (`id`),
 UNIQUE KEY `username` (`username`,`email`,`phone`)
);

CREATE TABLE `participation` (
 `id` int(255) NOT NULL AUTO_INCREMENT,
 `classid` int(11) NOT NULL,
 `studentid` int(11) NOT NULL,
 `grades` text,
 PRIMARY KEY (`id`)
);
