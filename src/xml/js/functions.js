var current = 0;

function getMediaCount() {
    return $("#mediaList > div").size();
}

function updateMetaData(index) {
    current = index;
    $("#title").text($("#" + index).find(".c0").text() + " - " + $("#" + index).find(".c1").text());
}

function updatePosition(position) {
    //$("#processing").css({width: position + "%"});
    $("#processing").animate({width: position + 0.3 +   "%"}, 500);
}

$(document).ready(function(){
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
           current = $target.attr("id");
           Operator.playOpause($target.attr("id"));
           $("#title").text($target.find(".c0").text() + " - " + $target.find(".c1").text());
       }
    });
    
    $("#random-mode, #repeat-mode, #signal-mode").bind("click", function(){
        Operator.setMode($(this).attr("pri"));
    });
    
    $("#process").click(function(event){
        Operator.setPosition(event.offsetX, $(this).width());
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
        if($("#voluming").css('display') === 'none') {
            $("#voluming").show();
            Operator.setMuted(0);
            $(this).find("img").attr("src", $(this).find("img").attr("osrc"));
        }
        else {
            $(this).find("img").attr("osrc",  $(this).find("img").attr("src")).attr("src", "qrc:/img/volume-muted.png");
            Operator.setMuted(1);
            $("#voluming").hide();
            
        }
    });
    
    Operator.setVolume(0.3);
    $("#volume-mute").find("img").attr("src", "qrc:/img/volume-low.png");
    $("#voluming").animate({width: "30%"}, 300).show();
});