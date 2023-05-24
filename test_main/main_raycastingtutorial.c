/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycastingtutorial.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:28:07 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/23 12:05:37 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D/includes/cub3D.h"

#define width 320
#define hight 200
#define PI 3.14159
double deg2rad(double degrees)
{
    return (degrees * (PI / 180));
}

const FOV_ANGLE = 60 * (PI / 180);
const NUM_RAYS = 320;

//rayAngle : littele slice of angle that i have to incremate
const   rayAngle = 0;
rayAngle += FOV_ANGLE / NUM_RAYS;



class player
{
    constractor(){
        this.x = window_width / 2;
        this.y = window_height / 2;
        this.radius = 3;
        thi.turnDirection = 0;     // -1 if left, +1 if right
        this.walkDirection = 0;     // -1 if back, +1 if front
        this.rotationAngle = PI / 2;  // each time i rotate this angle will be 90 degree(my rotation angle is 90 deree)
        this.moveSpeed = 2.0;  // how fast and slow is walking (how many pixel change when i move)
        this.rotationSpeed = 2 * (PI / 180); // how many angle(radium) i rotate 2 degree
    }
    update(){
        //TODO:
        // update player position based on turndirection and walkdirection
        console.log(this.turnDirection);
    }
    render(){
        noStroke();
        fill("red");
        circle(this.x, this.y, this.radius);
        stroke("red");
        line(
            this.x, 
            this.y,
            this.x + math.cos(this.rotationAngle) * 20,
            this.y + math. )
    }
}

var grid = new MAP();
var player = new player();

function Keypressd(){
    if (Keycode == UP_ARROW){
        player.walkDirection = +1;
    } else if (Keycode == DOWN_ARROW){
        player.walkDirection = -1;
    } else if (Keycode == RIGHT_ARROW){
        player.turnDirection = +1;
    } else if (Keycode == LEFT_ARROW){
        player.turnDirection = -1;
    }
}

function KeyReleased(){
    if (Keycode == UP_ARROW){
        player.walkDirection = 0;
    } else if (Keycode == DOWN_ARROW){
        player.walkDirection = 0;
    } else if (Keycode == RIGHT_ARROW){
        player.turnDirection = 0;
    } else if (Keycode == LEFT_ARROW){
        player.turnDirection = 0;
    }
}



function setup(){
    createCanvas(window_width, window_height);
}

function update(){
    player.update();
}

function draw(){
    updata();
    
    grid.render();
    player.render();
}






/* 1. subtract 30 degrees from the player rotation angle (FOV /2)
2. Start at cloumn 0
3. While(column < 320):
    cast a ray
    trace the ray until it intersects with a wall (map[i][j] == 1)
    record he inter section (x.y) and the distance(ray length)
    add the angle increment so the ray moves to the right
        rayAngle += 60 / 320; */

///////////////////////////////////////////////////////////////////////
//cast rays
///////////////////////////////////////////////////////////////////////

function castAllRays()
{
    var columnId = 0;

    //Start first ray subtracing half of the FOV
    var rayAngle = player.rotaionAngle - (FOV_ANGLE / 2);

    //Loop all columns casting rays
    for (var i = 0; i < NUM_RAYS; i++)
    {
        //call function to cast a single ray
        var ray = new Ray(rayAngle);
        ray.cast(columnId);
        
        //next ray is last ray incremented by FOV_ANGLE / NUM_RAY
        rayAngle += FOV_ANGLE / NUM_RAYS;
        
        columnId++;
    }
}


const TILE_SIZE = 64;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_STRIP_WIDTH = 1; 
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
    }
    hasWallAt(x, y) {
        if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
            return true;
        }
        var mapGridIndexX = Math.floor(x / TILE_SIZE);
        var mapGridIndexY = Math.floor(y / TILE_SIZE);
        return this.grid[mapGridIndexY][mapGridIndexX] != 0;
    }
    render() {
        for (var i = 0; i < MAP_NUM_ROWS; i++) {
            for (var j = 0; j < MAP_NUM_COLS; j++) {
                var tileX = j * TILE_SIZE;
                var tileY = i * TILE_SIZE;
                var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
            }
        }
    }
}