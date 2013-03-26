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
        $("#processing").css("width", 0);
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

function volume(value, flag) {
    var width = $("#volume").width(), height = $("#volume").height();
    var radius = (width >= height ? height:width)/2;
    var canvas = document.getElementById("volume");
    var context = canvas.getContext("2d");
    if(flag) {
        context.clearRect(0, 0, width, height);
    }
    context.beginPath();
    context.moveTo(width/2, height/2);
    context.arc(width/2, height/2, radius, 0, Math.PI * 2, false);
    context.fillStyle="#898989";
    context.fill();
    
    context.fillStyle="#CDCDCD";
    context.beginPath();
    context.moveTo(width/2, height/2);
    context.arc(width/2, height/2, radius, 0,(value>0?value : 0) * Math.PI * 2, false);
    context.fill();
    context.fillStyle="#9A9A9A";
    
    context.beginPath();
    context.moveTo(width/2, height/2);
    context.arc(width/2, height/2, radius - 5, 0, Math.PI * 2, false);
    context.fill();
    
    var img = new Image();
    img.src="qrc:/img/volume-" + (value > 0.8 ? "high" : (value > 0.4) ? "medium" : (value > 0.05) ? "low" : (value < 0) ? "muted":"zero") + ".png";
    img.onload = function() {
        context.drawImage(img, radius - 12, radius - 12, 24, 24);
    }
}

function wheelScroll(event) {
    Operator.setMuted(false);
    var interval = 0.05;
    var value =  Number($("#volume").attr("volume")) + interval * (event.wheelDelta > 0 ? 1 : -1);
    value = (value < 0 ? 0.01 : (value > 1 ? 0.99 : value));
    volume(value, true);
    Operator.setVolume(value);
    $("#volume").attr("volume", value);
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
    
    //init
    $("#volume").on("click", function(){
        if($(this).hasClass("muted")) {
            $(this).removeClass("muted");
            volume(Number($(this).attr("volume")), true);
            Operator.setMuted(false);
        }
        else {
            $(this).addClass("muted");
            Operator.setMuted(true);
            volume(-1, true);
        }
    }).attr("volume", 0.1);
    volume(0.1, false);
    Operator.setVolume(0.1);

    // call timer 
    window.setInterval(updatePosition, $("#processing").attr('interval'));
    document.getElementById("volume").onmousewheel=wheelScroll;
});
