function getMediaCount() {
    return $("#mediaList > div").size();
}

function updateMetaData(index) {
    $("#title").text($("#" + index).find(".c0").text() + " - " + $("#" + index).find(".c1").text());
    $("#mediaList").attr("current", index);
    $("#process").attr("duration", $("#" + index).find(".c2").attr("duration"))
    .find("#processing").attr("step", 
                              ($("#process").width() * $("#process").find("#processing").attr("interval")) 
                              / ($("#process").attr("duration") * 1000)).animate({width: 0}, 400);


    
//    // update attached picture
//    alert("here1" + Operator.pixmap);
//    Operator.pixmap.assignToHTMLImageElement(document.getElementById("attPicImg"));
//    alert("here2");
////    var context = document.getElementById("attPicCan").getContext("2d");
////    context.putImageData(myObject.myPixMap.toImageData());
//    alert("here");
}

function updatePosition() {
    if($("#playPause").hasClass("playing")) {
        $("#processing").css("width", $("#processing").width() + parseFloat($("#processing").attr("step")));
    }
    else {
        $("#processing").attr("width", 0);
    }
}

function mutedChanged(muted) {
    switch(muted) {
    case false:
        $("#volume-mute").find("img").attr("src", $("#volume-mute").find("img").attr("osrc"));
        $("#voluming").show();
        break;
    case true:
        $("#volume-mute").find("img").attr("osrc",  $("#volume-mute").find("img").attr("src")).attr("src", "qrc:/img/volume-muted.png");
        $("#voluming").hide();
        break;
    }
}

function stateChanged(state) {
    switch(state) {
    case 1:
        $("#playPause").addClass("playing").find('img').attr('src', 'qrc:/img/pause.png');
        break;
    default:
        $("#playPause").removeClass("playing").find('img').attr('src', 'qrc:/img/play.png');
    }
}

$(document).ready(function(){
    /* connections */
    Player.mutedChanged.connect(mutedChanged);
    Operator.stateChanged.connect(stateChanged);
    Operator.updateMetaData.connect(updateMetaData);
    
    $(".button").on("mouseover", function(){
        $(this).css('border-color', '#DEDEDE');
    })
    .on("mouseleave", function() {
        $(this).css("border-color", "#9D9D9D");
    });
    
    /* call Windows */
    $("#addMedia").click(function(){
        Operator.addMedia(getMediaCount());
    });
    
    $("#playPause").click(function(){
        Operator.playOpause(-1);
    });
    
    $("#previous").click(function(){
        Operator.previous();
    });
    
    $("#next").click(function(){
        Operator.next();
    });
    
    $("#mediaList").bind('dblclick', function(event) {
       if($(event.target).parent().is(".mediaRow")) {
           var $target = $(event.target).parent();
           Operator.playOpause($target.attr("id"));
       }
    });
    
    $("#random-mode, #repeat-mode, #signal-mode").bind("click", function(){
        Operator.setMode($(this).attr("pri"));
        $(".buttons_2").removeClass("actived");
        $(this).addClass("actived");
    });
    
    $("#process").click(function(event){
         if(parseInt($("#mediaList").attr("current")) >= 0) {
             Operator.setPosition(event.offsetX, $(this).width());
              $("#processing").css("width", event.offsetX);
         }
    });
    
    $("#volume-slider").click(function(event){
        var x = event.offsetX;
        var width = $(this).width();
        var per = x/width;
        Operator.setVolume(x, width);
        $(this).find("strong").animate({width: 100 * per +  "%"}, 300).show();
        if(per > 0.7)
            $("#volume-mute").find("img").attr("src", "qrc:/img/volume-high.png");
        else if(per > 0.3)
            $("#volume-mute").find("img").attr("src", "qrc:/img/volume-medium.png");
        else if(per >0 )
            $("#volume-mute").find("img").attr("src", "qrc:/img/volume-low.png");
        else 
            $("#volume-mute").find("img").attr("src", "qrc:/img/volume-zero.png");
    });
    
    $("#volume-mute").click(function(){
            Operator.setMuted();
    });
    
//    $(".buttons_2").click(function(){
//        $(".buttons_2").removeClass("actived");
//        $(this).addClass("actived");
//    });
    
    //init
    Operator.setVolume(0.2);
    $("#volume-mute").find("img").attr("src", "qrc:/img/volume-low.png");
    $("#voluming").animate({width: "20%"}, 300).show();

    // call timer 
    window.setInterval(updatePosition, $("#processing").attr('interval'));
    
});


/*
 var canvas = document.getElementById("volume");
      var context = canvas.getContext("2d");
      context.beginPath();
      context.moveTo(30, 30);
      context.arc(30, 30, 30, 0, Math.PI * 2, false);
      context.fillStyle="#AFAFAF";
      context.fill();
      
      context.fillStyle="#DEDEDE";
      context.beginPath();
      context.moveTo(30, 30);
      context.arc(30, 30, 30, 0, Math.PI * 0.6, true);
      context.fill();
      context.fillStyle="#9A9A9A";

      context.beginPath();
      context.moveTo(30, 30);
      context.arc(30, 30, 25, 0, Math.PI * 2, false);
      context.fill();
      //context.clearRect(0, 0, 80, 80);
    		var img = new Image();
      img.src="volume-high.png";
      img.onload = function() {
      	context.drawImage(img, 18, 18, 24, 24);
      }
*/
