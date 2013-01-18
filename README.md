Music Player With GStreamer

From the previous project named GMusic, i noticed that i lost the necessary documents for maintain the project.
I can't get the full understanding of a class immediately, including the properties and functions.


I don't want to understand it any more;So a new project is here.
the problems in my mind with the previous project:
    1. the struct of the project is very terrible
        though i divided the GUI into three parts as up, center and down.
        up deals with the buttons to play or stop. and it connect directly to the player backend.
        center deals with the play list, from which the player get the next music.
        down has the necessary menus such as delete, add, play model.
        then what's the problem?
        it's not the real MVC model. the problem comes from the component with Phonon. it's necessary to rewrite the component .
    2. it's CPU cost.
        it costs twice CPU times as players wrote by GTK. I don't admit that it's QT that cost double CPU times.
        the problem must come from the communications between threads.
        the rubbish struct desin leaded to the problem.
    3. the functions of this player is limited.
        at the begining, the player is desgin to have the ability to get the music infor from baidu database.
        and have the ability to show lricy, and play MV.but it limited.
    4. the outlook is ugliy. 
    i know nothing about UI design.



so what's the new desing?
the new desgin has two parts: front and backend , so it cares nothing about the GUI. 
and i can play medias under command line.and it's easy to add a GUI with GTK ot QT.
all these is desided by the uses.
the structure must be easy for threads communicate with each other.
there must some UNIX  domain socket or pipe communication.

socket and pipe is not CPU time COST.
and i need to define a protocol with necessary commands to control the backend.

or i can call it the media server and media client.

2012-11-08
