% Rooms
room(id, capacity, start_time, end_time, [equipment]).

% Courses
course(id, instructor, capacity, [hours], room).

% Instructors
instructor(id, [courses]).

% Students
student(id, [courses]).


room(r1, 50, 8, 17, [projector, smart_board]).
room(r2, 30, 12, 16, [projector]).
room(r3, 30, 10, 12, [projector]).


course(c1, i1, 30, [mon, wed], r1).
course(c2, i2, 40, [sun, tues], r2).
course(c3, i3, 20, [fri, thur], r2).


instructor(i1, [c1, c2]).
instructor(i2, [c2]).
instructor(i3, [c3]).


student(s1, [c1, c2]).
student(s2, []).
student(s3, [c3]).


conflict(Course) :-
    course(Course, _, _, Hours, Room),
    room(Room, _, Start, End, _),
    member(Day, Hours),
    
    (Start > Hour; End < Hour).


enroll(Student, Course) :-
    student(Student, Courses),
    
    \+ member(Course, Courses),
    course(Course, _, Capacity, _, _),
    
    count_students(Course, NumStudents),
    NumStudents < Capacity.

assing(Course, Room) :-
    course(Course, _, Capacity, Hours, _),
    room(Room, RoomCapacity, _, _, _),
   
    RoomCapacity >= Capacity,
    
    \+ conflict(Course, Room).


assing(Room, Course) :-
    assing(Course, Room).


count_students(Course, Count) :-
    findall(Student, student(Student, Courses), Students),
    count(Course, Students, Count).

count(_, [], 0).
count(Course, [H|T], Count) :-
    (member(Course, H) -> Count1 is 1; Count1 is 0),
    count(Course, T, Count2),
    Count is Count1 + Count2.

