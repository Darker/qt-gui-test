@echo off
echo Moving into node.js directory
cd client\nodejs
echo Now starting node
node test_from_file.js ip="localhost" port="9666" commands="commands1.js"
pause