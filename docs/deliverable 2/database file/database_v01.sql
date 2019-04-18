BEGIN TRANSACTION;
CREATE TABLE "users" (
	`username`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`password`	TEXT,
	`type`	TEXT,
	`name`	TEXT,
	`email address`	TEXT
);
INSERT INTO `users` VALUES(1,'','student','sina dee','sinadee@gmail.com');
INSERT INTO `users` VALUES(2,'','content manager','brad pitt','bpitt@sissymail.com');
CREATE TABLE `textbooks` (
	`isbn`	INTEGER,
	`title`	TEXT,
	`publisher`	TEXT,
	`authors`	TEXT,
	`year`	INTEGER,
	`edition`	TEXT,
	`description`	TEXT,
	`isAvailable`	TEXT,
	PRIMARY KEY(isbn)
);
CREATE TABLE `section` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`isAvailable`	TEXT DEFAULT 'no',
	`name`	TEXT,
	`number`	INTEGER,
	`description`	TEXT,
	`chapter id`	INTEGER
);
CREATE TABLE `course` (
	`courseCode`	TEXT,
	`courseName`	TEXT,
	PRIMARY KEY(courseCode)
);
CREATE TABLE `classlist` (
	`username`	TEXT,
	`courseCode`	TEXT,
	PRIMARY KEY(username)
);
CREATE TABLE `chapters` (
	`chapter_id`	INTEGER,
	`name`	TEXT,
	`number`	INTEGER,
	`isbn`	INTEGER,
	`description`	TEXT,
	`isAvailable`	TEXT,
	PRIMARY KEY(chapter_id)
);
;
;
COMMIT;
