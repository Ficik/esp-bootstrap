class MessageBus {

    constructor() {
        this.websocket = new WebSocket();
    }

}


const LogViewer = {
    template: "#log-viewer-template",
    data() {
      return {
          message: "Hello vue"
      }
    }
};

document.addEventListener("DOMContentLoaded", function(){
    console.log(new Vue({
        el: "#app",
        components: {
            LogViewer
        }
    }));
});
