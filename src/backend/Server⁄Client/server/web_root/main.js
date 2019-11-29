$(document).ready(function() {

 $("#boton1").click(function (event) {

        //stop submit the form, we will post it manually.
        event.preventDefault();

        // Get form
        var form = $('#form1')[0];

    // Create an FormData object 
        var data = new FormData(form);



    // disabled the submit button
        $("#boton1").prop("disabled", true);

        $.ajax({
            type: "POST",
            enctype: 'multipart/form-data',
            url: "/upload",
            data: data,
            processData: false,
            contentType: false,
            cache: false,
            timeout: 600000,
            dataType:'json',
            success: function (json) {

              $('#respuesta').text(json.respuesta);
              $('#tiempo').text(json.tiempo);

            },
            error: function (e) {
console.log(e);

            }
        });

    });


  var updateGraph = function(counter) {

  };

  // Create Websocket connection. For simplicity, no reconnect logic is here.
  var ws = new WebSocket('ws://' + location.host);
  ws.onmessage = function(ev) {
    updateGraph(ev.data);
  };
});
