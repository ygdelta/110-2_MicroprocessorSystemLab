const express = require("express");
const app = express();

var temp = "";
app.use(express.json());
app.use(express.static("./public"));

app.get("/",(req,res) => {
    const fileDirectory = __dirname;
    res.sendFile('./public/index2.html', {root: fileDirectory});
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

async function adc_value(){
    let child_process = await require("child_process");
    let process = await child_process.execFile('sudo', ['python','./python/lab5-1.py']);

    child_process.stdout.on('data', function(data)  {
    	temp = data;
    });
    child_process.stderr.on('data', (data) => {
        console.log(`stderr: ${data}`);
    });
}
app.get("/get",async(req,res) => {
    await adc_value();
    console.log(temp);
    res.set('Content-Type', 'appication/json');
    res.status(200).json({adc_value: temp}); 
 })

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log("On");
})
