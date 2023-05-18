/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycastingtutorial.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:28:07 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/18 18:07:21 by pmaimait         ###   ########.fr       */
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
        this.rotationAngle = PI / 2;  // each time i rotate tis angle will be 90 degree(my rotation angle is 90 deree)
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