
#define local_ip ""
#define local_port "8889"

#define tello_ip "192.168.10.1"
#define tello_port "8889"
#define tello_state_port "8890"
#define tello_video_port "11111"

struct cords{
    int x;
    int y;
    int z;
};

class TELLO{
    private:
        int speed;
        int height;
        int battery;
        int time;

        cords position;
    
    public:
        TELLO(int s, int h, int b, int t, cords p) : speed(s), height(h), battery(b), time(t), position(p) {}
};