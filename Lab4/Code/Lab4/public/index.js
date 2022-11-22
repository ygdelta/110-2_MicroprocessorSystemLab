
var qq=["off","off","off","off"];
function bt1(){
    var a = []
    a[0]=document.getElementById("c1").checked
    a[1]=document.getElementById("c2").checked
    a[2]=document.getElementById("c3").checked
    a[3]=document.getElementById("c4").checked
    for(var i=0;i<4;i++){
        console.log(a[i])
        if(document.getElementById("c5").checked){
            if(a[i]){
                qq[i] = "on"
            }
        }
        else{
            if(a[i]){
                qq[i] = "off"
            }
        }
      }
    var send={
        "enable":-1,
        "LED1": qq[0],
        "LED2": qq[1],
        "LED4": qq[3],
        "LED3": qq[2],
    }
    document.getElementById("LED_status").innerHTML=""
    for(var i =0;i<4;i++){
        document.getElementById("LED_status").innerHTML+="LED"+(i+1)+":"+qq[i]+"<br>"
    }

    console.log(send)
    fetch("/control", {
        body: JSON.stringify(send), // must match 'Content-Type' header
        cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
        credentials: 'same-origin', // include, same-origin, *omit
        headers: {
          'user-agent': 'Mozilla/4.0 MDN Example',
          'content-type': 'application/json'
        },
        method: 'POST', // *GET, POST, PUT, DELETE, etc.
        mode: 'cors', // no-cors, cors, *same-origin
        redirect: 'follow', // manual, *follow, error
        referrer: 'no-referrer', // *client, no-referrer
      })
      .then(response => response.json()) // 輸出成 json
    
}



function shine(){
    var a= document.getElementById("ss")
    var send={
        "enable": Number(a.value)
    }
    document.getElementById("shine").innerHTML ="Mode_Shine_Times: " + a.value;
    console.log(send)
    fetch("/control", {
        body: JSON.stringify(send), // must match 'Content-Type' header
        cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
        credentials: 'same-origin', // include, same-origin, *omit
        headers: {
          'user-agent': 'Mozilla/4.0 MDN Example',
          'content-type': 'application/json'
        },
        method: 'POST', // *GET, POST, PUT, DELETE, etc.
        mode: 'cors', // no-cors, cors, *same-origin
        redirect: 'follow', // manual, *follow, error
        referrer: 'no-referrer', // *client, no-referrer
      })
      .then(response => response.json()) // 輸出成 json
}
