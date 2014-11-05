# cuTPS
---

## Folder Structure

- common - Contains all classes that are common between the client and server
- resources - Contains all non source code files eg. SQL and DB files
- cuTPSServer - Contains all source code for the cuTPS server
- cuTPSClient - Contains all source code for the cuTPS client

## Build Instructions

- From a terminal, enter the cuTPSServer folder
 1. `$ qmake cuTPSServer.pro && make && ./cuTPSServer`
 
  or
 1.  `$ qmake cuTPSServer.pro`
 2.  `$ make`
 3.  `$ ./cuTPSServer`
- From another terminal, enter the cuTPSClient folder
 1. `$ qmake cuTPSClient.pro && make && ./cuTPSClient`
 
  or
 1.  `$ qmake cuTPSClient.pro`
 2.  `$ make`
 3.  `$ ./cuTPSClient`


## Test Cases

####1. Add Content
 This test case first adds a new textbook, chapter and then section to the database. It then tries to add the same ones again and should fail at doing so. Chapters and sections have a dependancy on a textbook (and a section on a chapter). We assume that on the client side it is not possible for a chapter or section to exist without it's proper dependancies.
 
####2. GetContent
 This test case first retrieves all of the content that would be retrieved for a student (in this case named peter). It then retrieves all of the content in the database.
 
####3. Add Invoice:
 This test case adds a student to an invoice object and adds the first textbook on the list retrieved by the get content test and adds it to the database. We assume that when a shopping cart is purchased this is the only information that will be stored on the database and that the client will not let a user try to purchase an empty cart.
 
####4. Run All tests
 This test case runs each test in the order presented here.
 
## Other functionality
- Field for setting IP address: default is local loopback, apply sets a new one
- Clear button: clears the response list

## JSON API Reference

Note that in all cases where an enum is used in the JSON examples below, 
it is referring to the value of the enum (ie. an integer) and not the enum
as a string.

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
  content: [ // Array of textbooks
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
  ]
}
```

### Add Textbook

**Request**

Stores a textbook in the database

```json
{
  command : ADD_TEXTBOOK,
  status : REQUEST,
  content : {
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


## Teamspeak 3 

Server: 104.236.54.27  
password: btfo  
