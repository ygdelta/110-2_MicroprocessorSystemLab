const express = require("express");
const app = express();

app.use(express.json());

app.get("/",(req,res) => {
    const fileDirectory = __dirname;
    res.sendFile('./public/index.html', {root: fileDirectory});
})

app.get("/index.js",(req,res) => {
    const fileDirectory = __dirname;
    res.sendFile('./public/index.js', {root: fileDirectory});
})

app.post("/control",(req,res) => {
    var inp = req.body;
    if(inp["enable"] < 0){
        LEDcontrol("LED1", inp["LED1"]);
        LEDcontrol("LED2", inp["LED2"]);
        LEDcontrol("LED3", inp["LED3"]);
        LEDcontrol("LED4", inp["LED4"]);
    }else{
        LEDcontrol("Mode_Shine", inp["enable"]);
    }
	res.end();
})

function wait(second) {
    let ChildProcess_ExecSync = require('child_process').execSync;
    ChildProcess_ExecSync('sleep ' + second);
};

function LEDcontrol(LED, power){
    let child_process = require("child_process");

    let process = child_process.execFile('sudo', ['./LAB2', LED, power]);
    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data', (data) => {
        console.log(`stderr: ${data}`);
    });
}

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log("On");
})
