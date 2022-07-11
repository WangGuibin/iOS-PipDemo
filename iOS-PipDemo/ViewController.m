//
//  ViewController.m
//  iOS-PipDemo
//
//  Created by 王贵彬 on 2022/7/11.
//

#import "ViewController.h"
#import "PipLyricsManager.h"

@interface ViewController ()

@property (nonatomic,strong) AVPlayer *player;
@property (nonatomic,strong) AVPlayerLayer *videoLayer;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"mp4"];
    NSURL *fileURL = [NSURL fileURLWithPath:path];
    AVPlayerItem *item = [AVPlayerItem playerItemWithURL:fileURL];
    AVPlayer *player = [AVPlayer playerWithPlayerItem:item];
    player.muted = YES;
    AVPlayerLayer *videoLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    self.videoLayer = videoLayer;
    [self.view.layer addSublayer:videoLayer];

    videoLayer.frame = CGRectMake(0, 0, self.view.bounds.size.width , 300);
    videoLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [player play];
    self.player = player;
    
    //第一步 设置 AVPlayerLayer
    [[PipLyricsManager shareTool] showPipWithPlayerLayer:self.videoLayer];
    
    UIButton *pipButton = [UIButton buttonWithType:(UIButtonTypeCustom)];
    if (@available(iOS 13.0, *)) {
        UIImage *normalImg = [[AVPictureInPictureController pictureInPictureButtonStartImage] imageWithRenderingMode:(UIImageRenderingModeAlwaysOriginal)];
        UIImage *selectImg = [[AVPictureInPictureController pictureInPictureButtonStopImage] imageWithRenderingMode:(UIImageRenderingModeAlwaysOriginal)];
        [pipButton setImage:normalImg forState:(UIControlStateNormal)];
        [pipButton setImage:selectImg forState:(UIControlStateNormal)];
    } else {
        // Fallback on earlier versions
    }
    pipButton.frame = CGRectMake(100, 320, 100 , 100);
    [pipButton addTarget:self action:@selector(pipAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:pipButton];

}

- (void)pipAction:(UIButton *)pipBtn{
    if (pipBtn.selected) {
        [[PipLyricsManager shareTool] startPictureInPicture];
    }else{
        [[PipLyricsManager shareTool] stopPictureInPicture];
    }
}

@end
