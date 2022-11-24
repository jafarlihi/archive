/* 
Inserts admin account 
*/
INSERT INTO logins 
	(id,username,password,access,email,name,surname,phone)
VALUES 
	(1,'admin','adminpass',2,'hikmat@jafarli.net','Hikmat','Jafarli',99466666666666);

/* 
Inserts 5 instructor accounts 
*/
INSERT INTO logins 
	(id,username,password,access,email,name,surname,phone)
VALUES 
	(2,'earnest1','password1',1,'earnest1@email.az','Earnest','Scholten',994661219901),
	(3,'karyl2','password2',1,'karyl2@email.az','Karyl','Carper',9946121290222),
	(4,'lissette3','password3',1,'lissette3@email.az','Lissette','Tant',99466048223),
	(5,'steven4','password4',1,'steven4@email.az','Steven','Accardi',9946779048221),
	(6,'nedra5','password5',1,'nedra5@email.az','Nedra','Pasch',994559847272);
	
/* 
Inserts 7 classes.
Class instructors (Class ID - Instructor username):
1, 2, 3 - earnest1
4, 5 - karyl2
6 - lissette3
7 - steven4
NULL - nedra5
*/
INSERT INTO classes 
	(id,name,info,teacherid)
VALUES 
	(1,'Programming 1','An introduction to computer programming for nonengineering and nonscience majors and for students considering taking CS 010 or CS 10V but needing additional preparation. Topics include the history of computing, basic computer operation, the notion of an algorithm, and programming constructs such as variables, expressions, input/output, branches, loops, functions, parameters, arrays, and strings. Credit is not awarded for CS 005 if it has already been awarded for CS 010 or CS 010V.',2),
	(2,'Logic Design','Covers design of digital systems. Includes Boolean algebra; combinational and sequential logic design; design and use of arithmetic logic units, carry-lookahead adders, multiplexors, decoders, comparators, multipliers, flip-flops, registers, and simple memories; state-machine design; and basic register-transfer level design. Uses hardware description languages, synthesis tools, programmable logic, and significant hardware prototyping. Cross-listed with EE 120A.',2),
	(3,'General Chemistry','CHEM 001A General Chemistry, 4 units. An introduction to the basic principles of chemistry. Credit is awarded for only one of CHEM 001A or CHEM 01HA.',2),
	(4,'English Writing','Covers ground rules of academic inquiry and exchange in English writing.',3),
	(5,'Linear Algebra','A study of matrices and systems of linear equations, determinants, Gaussian elimination, vector spaces, linear independence and linear transformation, orthogonality, eigenvalues, and eigenvectors. Also examines selected topics and applications.',3),
	(6,'Statistics for Business','An introduction to statistics using business applications. Topics include descriptive statistics, probability, discrete and continuous distributions, Bayes theorem, random variables, estimation and confidence intervals, hypothesis testing, analysis of variance, and simple linear regression.',4),
	(7,'Basic Music Concepts','MUS 001 Basic Musical Concepts, 4 units, Fundamentals of music, including notation, rhythm, major and minor scales, intervals, tonality, triads. Includes ear training, sight singing, and elementary analysis. Designed for students who need basic musical literacy. Open to nonmajors and those with no previous musical background.',5);
	
/* 
Inserts 10 student accounts 
*/	
INSERT INTO logins 
	(id,username,password,access,email,name,surname,phone)
VALUES 
	(7,'student1','studentpass1',0,'yswoodbetr4o_8e@4bnl82e87ixt.com','Osvaldo','Schurman',123452123321),
	(8,'student2','studentpass2',0,'kt09@arjnukr.com','Shirley','Richey',12345654432),
	(9,'student3','studentpass3',0,'jr1@duse94ay98t.com','Cinda','Canady',54334234433),
	(10,'student4','studentpass4',0,'ch6we@zuv99fiph.com','Garry','Emerson',91435346244),
	(11,'student5','studentpass5',0,'zy3if8f-9686man@ohf0l5s83p.com','Truman','Aden',21312314234),
	(12,'student5','studentpass6',0,'7k-@r9vhf1ckx0dr.com','Marian','Weishaupt',93274017245),
	(13,'student7','studentpass7',0,'tf62l4bej-91.@7tj5agoi.com','Karisa','Platter',94857399221),
	(14,'student8','studentpass8',0,'lx3k2ib@e1g9pr.com','Jarrod','Aceves',58382727646),
	(15,'student9','studentpass9',0,'x-osxnofxhf@3vndzyzp9.com','Jefferson','Smith',96872611344),
	(16,'student10','studentpass10',0,'ungr5yf@iicwzz0c5u.com','Gerardo','Swanger',50002131245);

/* 
Enrolls students to classes and inserts some grades.
Class enrollments (Student username - Class ID ("+" after Class ID if grade is entered)):
student1 - 1+, 2, 3+, 4+, 5+, 6, 7
student2 - 1, 2+, 5+, 6, 7
student3 - 2+, 4+, 6, 7
student4 - 1+, 3, 5
student5 - 1, 7
student6 - 4
student7 - NULL
student8 - NULL
student9 - NULL
student10 - NULL
*/	
INSERT INTO participation 
	(id,studentid,classid,grades)
VALUES
	(1, 7, 1, 'Midterm: 50<br>Final: 85'),
	(2, 7, 2, NULL),
	(3, 7, 3, 'Quiz: 40<br>Midterm: 55'),
	(4, 7, 4, 'Project: 100<br>Final: 95'),
	(5, 7, 5, 'Quiz 1: 50<br>Quiz 2: 53'),
	(6, 7, 6, 'Project 1: 79<br>Quiz 1: 41'),
	(7, 7, 7, 'Midterm: 60<br>Final: 64'),
	(8, 8, 1, NULL),
	(9, 8, 2, 'Quiz: 100<br>Midterm: Was absent'),
	(10, 8, 5, 'Midterm: 100<br>Final: 45'),
	(11, 8, 6, NULL),
	(12, 8, 7, NULL),
	(13, 9, 2, 'Project: 64<br>Final: 85'),
	(14, 9, 4, 'Quzi: 70<br>Final: 45'),
	(15, 9, 6, NULL),
	(16, 9, 7, NULL),
	(17, 10, 1, 'Midterm: 50<br>Final: 85'),
	(18, 10, 3, NULL),
	(19, 10, 5, NULL),
	(20, 11, 1, NULL),
	(21, 11, 7, NULL),
	(22, 12, 4, NULL);

/* 
Inserts forum posts
*/	
