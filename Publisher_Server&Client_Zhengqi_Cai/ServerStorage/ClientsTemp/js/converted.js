function toggleDIsplay(but){
    var butClass = but.classList[0];
    var targetclass = butClass.toLowerCase();
    console.log(targetclass);
var targets = document.getElementsByClassName(targetclass);
var omits = document.getElementsByClassName(targetclass+"Hidden");
    if(but.value == "show"){
        but.value = "hiden";
        for(var i=0;i<targets.length ;i++){
            targets[i].style.setProperty("display", "none");
        }
        for(var i=0;i<omits.length; i++){
            omits[i].style.setProperty("display","inline");
        }
    }else{
        but.value = "show";
        for(var i=0;i< targets.length;i++){
            targets[i].style.setProperty("display", "inline");
        }
        for(var i=0;i<omits.length; i++){
            omits[i].style.setProperty("display","none");
        }
    }
}

