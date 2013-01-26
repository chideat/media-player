function getMediaCount() {
    return $("#mediaList > div").size();
}

$(document).ready(function(){
    /* call Windows */
    $("#addMedia").click(function(){
        Operator.addMedia(getMediaCount());
    });
    
    $("#playPause").click(function(){
        Operator.playOpause(-1);
    });
    
    $("#mediaList").bind('dblclick', function(event) {
       if($(event.target).parent().is(".mediaRow")) {
           var $target = $(event.target).parent();
           Operator.playOpause($target.attr("id"));
           $("#title").text($target.find(".c0").text() + " - " + $target.find(".c1").text());
       }
    });
});