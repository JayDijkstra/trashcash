/**
 * Created by Jay on 7/6/2015.
 */
$(document).ready(function(){
    window.setInterval(function(){
        $.get('ajax/name.php', function(data){
            $("#points-overview").html(data);
        });
    }, 200);

});

