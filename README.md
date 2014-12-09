# cuTPS
---

## Folder Structure

- common - Contains all classes that are common between the client and server
- resources - Contains all non source code files eg. SQL and DB files
- cuTPSServer - Contains all source code for the cuTPS server
- cuTPSClient - Contains all source code for the cuTPS client

## Build Instructions

- From a terminal, enter the cuTPSServer folder
  1.  `$ qmake cuTPSServer.pro`
  2.  `$ make`
  3.  `$ ./cuTPSServer`
- From another terminal, enter the cuTPSClient folder
  1.  `$ qmake cuTPSClient.pro`
  2.  `$ make`
  3.  `$ ./cuTPSClient`

## JSON API Reference

Note that in all cases where an enum is used in the JSON examples below, 
it is referring to the value of the enum (ie. an integer) and not the enum
as a string.

### Login

**Request**

```json
{
  command : LOGIN,
  status : REQUEST,
  user : {
    username : "bob",
    name : "",
    password : "xxxxxxx",
    type : ""
  }
}
```

**Response**

```json
{
  command : LOGIN,
  status : SUCCESS,
  user : {
    username : "bob",
    name : "Bobby",
    password : "xxxxxxx",
    type : "student"
  }
}
```



### Retrieve Content

**Request**

Retrieves a list of content (textbooks, chapters, sections) for a user

```json
{
  command : GET_CONTENT,
  status : REQUEST,
  username: "bob"
}
```

**Response**

```json
{
  command : GET_CONTENT,
  status : SUCCESS,
  classes: [ // Array of classes
    {
      semester : "FALL 2014",
      course : {
        courseCode : "COMP 3004",
        courseTitle : "Intro to Software Engineering"
      },
      booklist : [
      {
        isbn : "1234567890",
        title : "Book title",
        publisher : "John Doe",
        author : "Jane Doe",
        year : 2014,
        edition : "1",
        description : "Here is a book description",
        available : true,
        price : 25.75,
        content_id : 1,
        chapters : [ // Array of chapters
        {
          title : "Chapter 1",
          chapterNo : 1,
          description : "Chapter 1 description",
          available : true,
          price : 15.50,
          content_id : 2,
          sections : [ // Array of sections
          {
            title : "Section 1"
            sectionNo : 1,
            description : "Section 1 description",
            available : true,
            price : 5.15,
            content_id : 3
          },
          // More sections
          ]
        },
        // More chapters
        ]
      },
      // More textbooks...
      ],
      studentlist : [
      {
        username : "bob",
        name : "Bobby Boucher"
      },
      // More students (unless this request was for a student, then that student will be the only user in this list
      ]
    }
}
```

### Add Textbook

**Request**

Stores a textbook in the database

```json
{
  command : ADD_TEXTBOOK,
  status : REQUEST,
  serialized : {
    semester : "FALL 2014",
    course : {
      courseCode : "COMP 3004",
      courseTitle : ""
    }
    booklist : [{
      isbn : "1234567890",
      title : "Book title",
      publisher : "John Doe",
      author : "Jane Doe",
      year : 2014,
      edition : "1",
      description : "Here is a book description",
      available : true,
      price : 25.75
    }]
  }
}
```

**Response**

```json
{
  command : ADD_TEXTBOOK,
  status : SUCCESS
}
```

### Add Chapter

**Request**

Stores a chapter in the database

```json
{
  command : ADD_CHAPTER,
  status : REQUEST,
  content : {
      title : "Chapter 1",
      chapterNo : 1,
      description : "Chapter 1 description",
      available : true,
      price : 15.50,
      content_id : 2,
      ISBN : "1234567890"
  }
}
```

**Response**

```json
{
  command : ADD_CHAPTER,
  status : SUCCESS
}
```

### Add Section

**Request**

Stores a section in the database

```json
{
  command : ADD_SECTION,
  status : REQUEST,
  content : {
      title : "Section 1"
      sectionNo : 1,
      description : "Section 1 description",
      available : true,
      price : 5.15,
      content_id : 3
      ISBN : "1234567890",
      chapterNo : 1
  }
}
```

**Response**

```json
{
  command : ADD_SECTION,
  status : SUCCESS
}
```

### Add Invoice

**Request**

Stores an invoice in the database

```json
{
  command : ADD_INVOICE,
  status : REQUEST,
  invoice : {
    username : "bob",
    contents : [ // Array of content IDs
      {
        cid : 1
      },
      {
        cid : 2
      },
      // More cid objects...
    ]
  }
}
```

**Response**

```json
{
  command : ADD_INVOICE,
  status : SUCCESS
}
```

### Errors

If the status of a response is ERROR instead of SUCCESS it will be formatted as follows:

**Response**

```json
{
  command : [COMMAND_T],
  status : ERROR,
  message : "A useful and informative error message"
}
```

... More to follow in deliverable 4

## Database Structure

### Users

| username | password | type | name |
| --- | --- | --- | --- |
| text - not null | text - not null | text - not null | text - not null |

*Note*: We need another table for user types. Make it a foreign key dependency of Users.type

### Courses

| code | name |
| --- | --- |
| text - not null| text - not null |

*Note*: We need a new table for semesters. This also means we need a new entity object possible called class.
A class will have a course, the semester its in and the students in it.

### Content

This table is used as a way to uniquely identify each textbook, chapter, section
across all their tables.

| id |
|---|
|int|

*Note*: We may need to add a column to this table that specifies type but only if
we can use that column to specify what table to look in when querying content by
its content id.  If it's not possible and the only way is to look in each content
table (Textbooks, Chapter, Sections) until the content id is found then the type
column is irrelevant.

### Textbooks

|isbn|title|publisher|author|year|edition|description|availability|price|content_id|
|---|---|---|---|---|---|---|---|---|---|
|text - not null|text - not null| text - not null|text - not null|integer - not null|text|text|integer (bool) - not null|real (float) - not null|integer - not null|

### Chapters

|name|number|textbook|description|availability|price|content_id|
|---|---|---|---|---|---|---|
|text - not null|integer - not null|text - not null|text|integer (bool) - not null|real (float) - not null|integer - not null|

### Sections

|name|number|chapter|textbook|description|availability|price|content_id|
|---|---|---|---|---|---|---|---|
|text - not null|integer - not null|integer - not null|text - not null|text|integer (bool) - not null|real (float) - not null|integer - not null|

### Book_List

|textbook_id|course_code|
|---|---|
|text - not null|text - not null|

*Note*: The course code will change so it references a class and not a course
since the books for a course may vary by semester

### Class_list

|student|course_code|
|---|---|
|text - not null|text - not null|

*Note* - We need to add a semester column to this table


# Useful info
---

## Git Setup

1. Set your name `git config --global user.name "John Doe"`
2. Set your email `git config --global user.email johndoe@example.com`
3. Optional, set some other settings
  - `git config --global color.status auto`
  - `git config --global color.branch auto`
  - `git config --global color.interactive auto`
  - `git config --global color.diff auto`

For all Git related issues see this [site](http://git-scm.com/doc).  Don't be lazy, read and google. 
There's LOTS of documentation.

## Repository Setup

1. Make sure you have [SSH keys](https://gitlab.com/profile/keys) setup. [Help](https://gitlab.com/help/ssh/ssh)
2. Create project directory
3. Initialize the repository `git init`
4. Set the remote repository you want to track and call it origin `git remote add origin git@gitlab.com:team-do-not-stick-in-ear/cutps.git`
5. Pull the files from the master branch on origin to your local machine `git pull origin master`
6. If you don't want to type 'origin master' every time you push or pull then:
  - If you're in the 3004 VM `git branch --set-upstream master origin/master`
  - If your're **not** in the 3004 VM `git branch -u origin/master`

## IRC 

Server: irc.freenode.net  
Room: #stickinear  
Logger: http://104.236.54.27/  