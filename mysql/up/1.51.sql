DROP TABLE IF EXISTS `domain`;

CREATE TABLE `domain` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `host` varchar(128) NOT NULL,
  `master` varchar (255) NOT NULL,
  `updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `user_id` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8; 