#include <stdlib.h>

volatile int pixel_buffer_start; // global variable

#define BLACK 0xFFFF
#define WIDTH 320
#define HEIGHT 240

volatile int pixel_buffer_start; // global variable
int hasLadder[WIDTH][HEIGHT], hasSnake[WIDTH][HEIGHT];

void draw_line(int x0, int x1, int y0, int y1, short int line_color);
void draw_yline(int x,  short int line_color);
void draw_xline(int  y,  short int line_color);
void draw_board();
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int x0, int x1);
void wait_for_vsync();
void wait_for_button();

void draw_player(int x, int y, short int color); // player is a 10x10 black box
void draw_ladders();
void draw_shoots();
void draw_one(int x,int y);
void draw_two(int x,int y);
void draw_three(int x,int y);
void draw_four(int x,int y);
void draw_five(int x,int y);
void draw_six(int x,int y);
void draw_seven(int x,int y);
void draw_eight(int x,int y);
void draw_nine(int x,int y);
void draw_zero(int x,int y);
void draw_numbers();
int fill_rand(int* ptr, int a, int b); // fill ptr with a random number in [a, b]

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    memset(hasLadder, 0, sizeof hasLadder);
    memset(hasSnake, 0, sizeof hasSnake);
    //int xpoints[8];
    
    
    
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    /* set front pixel buffer to start of FPGA On-chip memory */
    /* now, swap the front/back buffers, to set the front buffer location */
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen();
    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        
        
        
        

            

        // code for drawing the boxes and lines (not shown)
        // code for updating the locations of boxes (not shown)
        
    
       //Insert game logic
        
        draw_board();
        draw_ladders();
        draw_shoots();
        draw_numbers();
        

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        
        //Erase
        
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
        
        
        
        
        
    }
}

// code for subroutines (not shown)

void draw_player(int x, int y, short int color) {
	#define SIZE 10
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			plot_pixel(x+i, y+j, color);
		}
	}
}

void wait_for_vsync(){
    
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    *pixel_ctrl_ptr = 1;
    register int temp = *(pixel_ctrl_ptr+3);
    while((temp & 0x01) != 0) {
        temp = *(pixel_ctrl_ptr+3);
    }
    
}

void wait_for_button() {
	volatile int * key_ctrl_ptr = (int *) 0xFF200050; // base address for pushbuttons on de1soc
	
	while(*(key_ctrl_ptr + 3) == 0); // wait for edge capture register
	*(key_ctrl_ptr+3) = 1; // write to clear edge cature
}

void draw_ladders(){
    draw_line(62+30*1,218-30*2,62+30*3,218-30*6,0x07C0);
    draw_line(62+30*5,218-30*1,62+30*3,218-30*4,0x07C0);
    draw_line(62+30*5,218-30*5,62+30*6,218-30*7,0x07C0);
}
void draw_shoots(){
    draw_line(62+30*0,218-30*1,62+30*5,218-30*0,0xFC00);
    draw_line(62+30*4,218-30*4,62+30*7,218-30*3,0xFC00);
    draw_line(62+30*3,218-30*7,62+30*0,218-30*4,0xFC00);
}

void draw_one(int x,int y){
    plot_pixel(x+3, y+5, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+3, 0x0000);
    plot_pixel(x+5, y+2, 0x0000);
    plot_pixel(x+5, y+3, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+5, y+5, 0x0000);
    plot_pixel(x+5, y+6, 0x0000);
    plot_pixel(x+5, y+7, 0x0000);
    plot_pixel(x+5, y+8, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+5, y+10, 0x0000);
    plot_pixel(x+5, y+11, 0x0000);
    plot_pixel(x+5, y+12, 0x0000);
    plot_pixel(x+5, y+13, 0x0000);
    plot_pixel(x+5, y+14, 0x0000);
    plot_pixel(x+5, y+15, 0x0000);
    plot_pixel(x+4, y+15, 0x0000);
    plot_pixel(x+3, y+15, 0x0000);
    plot_pixel(x+6, y+15, 0x0000);
    plot_pixel(x+7, y+15, 0x0000);
}
void draw_two(int x,int y){
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+3, y+6, 0x0000);
    plot_pixel(x+4, y+6, 0x0000);
    plot_pixel(x+5, y+6, 0x0000);
    plot_pixel(x+6, y+6, 0x0000);
    plot_pixel(x+7, y+7, 0x0000);
    plot_pixel(x+7, y+8, 0x0000);
    plot_pixel(x+7, y+9, 0x0000);
    plot_pixel(x+6, y+10, 0x0000);
    plot_pixel(x+5, y+11, 0x0000);
    plot_pixel(x+4, y+12, 0x0000);
    plot_pixel(x+3, y+13, 0x0000);
    plot_pixel(x+2, y+14, 0x0000);
    plot_pixel(x+3, y+14, 0x0000);
    plot_pixel(x+4, y+14, 0x0000);
    plot_pixel(x+5, y+14, 0x0000);
    plot_pixel(x+6, y+14, 0x0000);
    plot_pixel(x+7, y+14, 0x0000);
}
void draw_three(int x,int y){
    plot_pixel(x+3, y+5, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+7, y+6, 0x0000);
    plot_pixel(x+7, y+7, 0x0000);
    plot_pixel(x+6, y+8, 0x0000);
    plot_pixel(x+5, y+8, 0x0000);
    plot_pixel(x+4, y+8, 0x0000);
    plot_pixel(x+7, y+9, 0x0000);
    plot_pixel(x+7, y+10, 0x0000);
    plot_pixel(x+7, y+11, 0x0000);
    plot_pixel(x+6, y+12, 0x0000);
    plot_pixel(x+5, y+12, 0x0000);
    plot_pixel(x+4, y+12, 0x0000);
    plot_pixel(x+3, y+11, 0x0000);
}
void draw_four(int x,int y){
    plot_pixel(x+2, y+4, 0x0000);
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+2, y+9, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+6, y+5, 0x0000);
    plot_pixel(x+6, y+6, 0x0000);
    plot_pixel(x+6, y+7, 0x0000);
    plot_pixel(x+6, y+8, 0x0000);
    plot_pixel(x+6, y+9, 0x0000);
    plot_pixel(x+6, y+10, 0x0000);
    plot_pixel(x+6, y+11, 0x0000);
    plot_pixel(x+6, y+12, 0x0000);
    plot_pixel(x+6, y+13, 0x0000);
    plot_pixel(x+6, y+14, 0x0000);
    plot_pixel(x+3, y+9, 0x0000);
    plot_pixel(x+4, y+9, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    
}
void draw_five(int x,int y){
    plot_pixel(x+6, y+5, 0x0000);
    plot_pixel(x+5, y+5, 0x0000);
    plot_pixel(x+4, y+5, 0x0000);
    plot_pixel(x+3, y+5, 0x0000);
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+2, y+9, 0x0000);
    plot_pixel(x+3, y+9, 0x0000);
    plot_pixel(x+4, y+9, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+6, y+10, 0x0000);
    plot_pixel(x+6, y+11, 0x0000);
    plot_pixel(x+6, y+12, 0x0000);
    plot_pixel(x+2, y+12, 0x0000);
    plot_pixel(x+3, y+13, 0x0000);
    plot_pixel(x+4, y+13, 0x0000);
    plot_pixel(x+5, y+13, 0x0000);
}
void draw_six(int x,int y){
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+3, y+4, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+2, y+9, 0x0000);
    plot_pixel(x+2, y+10, 0x0000);
    plot_pixel(x+2, y+11, 0x0000);
    plot_pixel(x+2, y+12, 0x0000);
    plot_pixel(x+3, y+13, 0x0000);
    plot_pixel(x+4, y+13, 0x0000);
    plot_pixel(x+5, y+13, 0x0000);
    plot_pixel(x+6, y+13, 0x0000);
    plot_pixel(x+3, y+9, 0x0000);
    plot_pixel(x+4, y+9, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+6, y+9, 0x0000);
    plot_pixel(x+7, y+10, 0x0000);
    plot_pixel(x+7, y+11, 0x0000);
    plot_pixel(x+7, y+12, 0x0000);
}
void draw_seven(int x,int y){
    plot_pixel(x+2, y+4, 0x0000);
    plot_pixel(x+3, y+4, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+7, y+4, 0x0000);
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+7, y+6, 0x0000);
    plot_pixel(x+6, y+7, 0x0000);
    plot_pixel(x+6, y+8, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+5, y+10, 0x0000);
    plot_pixel(x+4, y+11, 0x0000);
    plot_pixel(x+4, y+12, 0x0000);
    plot_pixel(x+3, y+13, 0x0000);
    plot_pixel(x+3, y+14, 0x0000);
}
void draw_eight(int x,int y){
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+7, y+6, 0x0000);
    plot_pixel(x+7, y+7, 0x0000);
    plot_pixel(x+7, y+8, 0x0000);
    plot_pixel(x+2, y+10, 0x0000);
    plot_pixel(x+2, y+11, 0x0000);
    plot_pixel(x+2, y+12, 0x0000);
    plot_pixel(x+2, y+13, 0x0000);
    plot_pixel(x+7, y+10, 0x0000);
    plot_pixel(x+7, y+11, 0x0000);
    plot_pixel(x+7, y+12, 0x0000);
    plot_pixel(x+7, y+13, 0x0000);
    plot_pixel(x+3, y+4, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+3, y+9, 0x0000);
    plot_pixel(x+4, y+9, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+6, y+9, 0x0000);
    plot_pixel(x+3, y+14, 0x0000);
    plot_pixel(x+4, y+14, 0x0000);
    plot_pixel(x+5, y+14, 0x0000);
    plot_pixel(x+6, y+14, 0x0000);
    
}
void draw_nine(int x,int y){
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+7, y+4, 0x0000);
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+7, y+6, 0x0000);
    plot_pixel(x+7, y+7, 0x0000);
    plot_pixel(x+7, y+8, 0x0000);
    plot_pixel(x+7, y+9, 0x0000);
    plot_pixel(x+7, y+10, 0x0000);
    plot_pixel(x+7, y+11, 0x0000);
    plot_pixel(x+7, y+12, 0x0000);
    plot_pixel(x+7, y+13, 0x0000);
    plot_pixel(x+7, y+14, 0x0000);
    plot_pixel(x+7, y+15, 0x0000);
    plot_pixel(x+3, y+4, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+6, y+4, 0x0000);
    plot_pixel(x+3, y+9, 0x0000);
    plot_pixel(x+4, y+9, 0x0000);
    plot_pixel(x+5, y+9, 0x0000);
    plot_pixel(x+6, y+9, 0x0000);
}
void draw_zero(int x,int y){
    plot_pixel(x+7, y+5, 0x0000);
    plot_pixel(x+7, y+6, 0x0000);
    plot_pixel(x+7, y+7, 0x0000);
    plot_pixel(x+7, y+8, 0x0000);
    plot_pixel(x+7, y+9, 0x0000);
    plot_pixel(x+7, y+10, 0x0000);
    plot_pixel(x+7, y+11, 0x0000);
    plot_pixel(x+7, y+12, 0x0000);
    plot_pixel(x+7, y+13, 0x0000);
    plot_pixel(x+7, y+14, 0x0000);
    plot_pixel(x+2, y+5, 0x0000);
    plot_pixel(x+2, y+6, 0x0000);
    plot_pixel(x+2, y+7, 0x0000);
    plot_pixel(x+2, y+8, 0x0000);
    plot_pixel(x+2, y+9, 0x0000);
    plot_pixel(x+2, y+10, 0x0000);
    plot_pixel(x+2, y+11, 0x0000);
    plot_pixel(x+2, y+12, 0x0000);
    plot_pixel(x+2, y+13, 0x0000);
    plot_pixel(x+2, y+14, 0x0000);
    plot_pixel(x+3, y+4, 0x0000);
    plot_pixel(x+4, y+4, 0x0000);
    plot_pixel(x+5, y+4, 0x0000);
    plot_pixel(x+3, y+15, 0x0000);
    plot_pixel(x+4, y+15, 0x0000);
    plot_pixel(x+5, y+15, 0x0000);
}

void draw_numbers(){
    for(int i = 0; i < 64 ; i++){
        int tens = i/10;
        int ones = i%10;
        int x = i%8;
        int y = i/8;
        switch(tens){
            case 1: draw_one(40+30*x,210-30*y);break;
            case 2: draw_two(40+30*x,210-30*y);break;
            case 3: draw_three(40+30*x,210-30*y);break;
            case 4: draw_four(40+30*x,210-30*y);break;
            case 5: draw_five(40+30*x,210-30*y);break;
            case 6: draw_six(40+30*x,210-30*y);break;
            default :;
        }
        
        switch(ones){
            case 0: draw_zero(55+30*x,210-30*y);break;
            case 1: draw_one(55+30*x,210-30*y);break;
            case 2: draw_two(55+30*x,210-30*y);break;
            case 3: draw_three(55+30*x,210-30*y);break;
            case 4: draw_four(55+30*x,210-30*y);break;
            case 5: draw_five(55+30*x,210-30*y);break;
            case 6: draw_six(55+30*x,210-30*y);break;
            case 7: draw_seven(55+30*x,210-30*y);break;
            case 8: draw_eight(55+30*x,210-30*y);break;
            case 9: draw_nine(55+30*x,210-30*y);break;
            default :;
        }
    }
}

// code not shown for clear_screen() and draw_line() subroutines

void draw_board(){
    for(int a = 0; a< 8 ; a++){
        
        //box1
        draw_yline(40 + a*30, 0x0000);
        draw_yline(69 + a*30, 0x0000);
        
    }
    for(int a = 0; a< 8 ; a++){
        
        //box1
        draw_xline(0  + a*30, 0x0000);
        draw_xline(29 + a*30, 0x0000);
        
    }
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color){
    int is_steep = abs(y1 - y0) > abs(x1 - x0);
    if(is_steep){
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if(x0 > x1){
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax /2);
    int y = y0;
    int y_step;
    if(y0 < y1){
        y_step = 1;
    }else{
        y_step = -1;
    }
    for(int x = x0 ; x < x1 ; x++){
        if(is_steep){
            plot_pixel(y,x,line_color);
        }else{
            plot_pixel(x,y,line_color);
        }
        error = error + deltay;
        if(error >= 0){
            y = y + y_step;
            error = error - deltax;
        }
    }
        
}

void draw_xline( int y, short int line_color){
    
    for(int x = 40 ; x < 280 ; x++){
        plot_pixel(x,y,line_color);
    }
        
}
void draw_yline( int x, short int line_color){
    
    for(int y = 0 ; y < 240 ; y++){
        plot_pixel(x,y,line_color);
    }
        
}

void clear_screen(){
    for(int x = 0 ; x < 320 ; x++){
        for(int y = 0 ; y < 240 ; y++){
            plot_pixel(x,y,0xFFFF);
        }
    }
}



void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

int fill_rand(int* ptr, int a, int b) {
	return *ptr = a + rand() % (b - a + 1);
}
