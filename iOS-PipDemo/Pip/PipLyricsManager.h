//
//  PipLyricsManager.h
//  PipLyricsManagerDemo
//
//  Created by 王贵彬 on 2022/7/11.
//
// 参考了 https://github.com/CaiWanFeng/CustomPictureInPicture

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVKit/AVKit.h>

typedef NS_ENUM(NSUInteger, PipLyricsType) {
    PipLyricsTypeSingleLine = 1, // 一行展示 类似歌词 
    PipLyricsTypeSquare11, //正方形 1:1
    PipLyricsTypeSquare23, // 2:3
    PipLyricsTypeSquare169,// 16:9
    PipLyricsTypeSquare16// 1:6
};

NS_ASSUME_NONNULL_BEGIN

@interface PipLyricsManager : NSObject

//单例
+ (PipLyricsManager *)shareTool;

//是否成功开启了画中画~
@property (nonatomic,assign) BOOL isInPip;
/**
 //播放器需要提供 AVPlayerLayer  作为参数传入
 NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"mp4"];
 NSURL *fileURL = [NSURL fileURLWithPath:path];
 AVPlayerItem *item = [AVPlayerItem playerItemWithURL:fileURL];
 AVPlayer *player = [AVPlayer playerWithPlayerItem:item];
 player.muted = YES;
 AVPlayerLayer *videoLayer = [AVPlayerLayer playerLayerWithPlayer:player];
 self.videoLayer = videoLayer;
 [self.view.layer addSublayer:videoLayer];
 [self.view.layer insertSublayer:videoLayer atIndex:0];
 videoLayer.frame = CGRectMake(0, 0, videoWidth , videoHeight);
 videoLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
 [player play];
 self.player = player;
 
 //按钮图片系统提供
 if (@available(iOS 13.0, *)) {
     UIImage *normalImg = [[AVPictureInPictureController pictureInPictureButtonStartImage] imageWithRenderingMode:(UIImageRenderingModeAlwaysOriginal)];
     UIImage *selectImg = [[AVPictureInPictureController pictureInPictureButtonStopImage] imageWithRenderingMode:(UIImageRenderingModeAlwaysOriginal)];
     [pipButton setImage:normalImg forState:(UIControlStateNormal)];
     [pipButton setImage:selectImg forState:(UIControlStateNormal)];
 } else {
     // Fallback on earlier versions
 }

//按钮回调里处理
 if (pipBtn.selected) {
     [[PipLyricsManager shareTool] showPipWithPlayerLayer:self.videoLayer];
    //需要延时一下 不然画中画容易启动失败
     dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
         [[PipLyricsManager shareTool] startPictureInPicture];
     });
 }else{
     [[PipLyricsManager shareTool] stopPictureInPicture];
 }
 */

//MARK - 对接自定义播放器的画中画 此方法的画中画比例形状与pipType无关,与实际播放器视频尺寸有关
- (void)showPipWithPlayerLayer:(AVPlayerLayer *)playerLayer;
//开启画中画
- (void)startPictureInPicture;
//停止画中画
- (void)stopPictureInPicture;

////// 以下为提词器相关 ////////
/**
 [PipLyricsManager shareTool].pipType = PipLyricsTypeSquare11;
 [PipLyricsManager shareTool].textColor = [UIColor orangeColor];
 [PipLyricsManager shareTool].alignment = NSTextAlignmentCenter;
 [PipLyricsManager shareTool].textFont = kMonoFont(20);
 [PipLyricsManager shareTool].text = @"\n君不见黄河之水天上来\n\
 奔流到海不复回\n\
 君不见高堂明镜悲白发\n\
 朝如青丝暮成雪\n\
 人生得意须尽欢\n\
 莫使金樽空对月\n\
 天生我材必有用\n\
 千金散尽还复来\n\
 人生得意须尽欢\n\
 莫使金樽空对月\n\
 烹羊宰牛且为乐\n\
 会须一饮三百杯\n\
 岑夫子\n\
 丹丘生\n\
 将进酒\n\
 杯莫停\n\
 与君歌一曲\n\
 请君为我侧耳听\n\
 钟鼓馔玉不足贵\n\
 但愿长醉不复醒\n\
 古来圣贤皆寂寞\n\
 惟有饮者留其名\n\
 陈王昔时宴平乐\n\
 斗酒十千恣欢谑\n\
 主人何为言少钱\n\
 径须沽取对君酌\n\
 五花马\n\
 千金裘\n\
 呼儿将出换美酒\n\
 将进酒 将进酒 与尔同销万古愁\n\
 五花马\n\
 千金裘\n\
 呼儿将出换美酒\n\
 将进酒 将进酒 与尔同销万古愁\n";
 [[PipLyricsManager shareTool] showLyricsWithSuperView:self.view];
 [SVProgressHUD setDefaultStyle:(SVProgressHUDStyleDark)];
 [SVProgressHUD setDefaultMaskType:(SVProgressHUDMaskTypeBlack)];
 [SVProgressHUD setDefaultAnimationType:(SVProgressHUDAnimationTypeNative)];
 [SVProgressHUD show];
 dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
     [SVProgressHUD dismiss];
     [[PipLyricsManager shareTool] startPictureInPicture];
 });
 */

@property (nonatomic,assign) PipLyricsType pipType; //默认 PipLyricsTypeSingleLine

@property (nonatomic, assign) NSInteger preferredFramesPerSecond; //播放帧率 默认24
@property (nonatomic, assign) CGFloat lineSpacing;
@property (nonatomic, assign) NSTextAlignment alignment;
@property (nonatomic, strong, nullable) UIFont *textFont;
@property (nonatomic, strong, nullable) UIColor *textColor; //默认白色
@property (nonatomic, strong, nullable) UIColor *backgroundColor; //默认黑色
@property (nonatomic, copy, nonnull) NSString *text;//不可为空
@property (nonatomic, copy, nullable) NSAttributedString *attributeText;

//旋转 
- (void)rotate;
//切换形态
- (void)transformWithPipType:(PipLyricsType)pipType;

//配置提词器设置完后调用展示
@property (nonatomic,assign) BOOL isShowLyrics;//默认NO 只有调用 showWithSuperView: 才是YES
/// @param superView 宿主父视图
- (void)showLyricsWithSuperView:(UIView *)superView;
//显示控制台打印日志 (退到后台日志无法打印 只能前台打印...)
@property (nonatomic,assign) BOOL isConsoleLog; //默认NO 只有调用了showConsoleLogWithSuperView: 才会改为YES

/**
    示例:
 [PipLyricsManager shareTool].pipType = PipLyricsTypeSingleLine;//展示日志建议用PipLyricsTypeSquare11
 [[PipLyricsManager shareTool] showConsoleLogWithSuperView:self.view];
 [[PipLyricsManager shareTool] addLastLineText:@"这是歌词展示"];
 dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
     [[PipLyricsManager shareTool] startPictureInPicture];
 });

 //适当的时机进行更新显示不同的歌词
 NSArray *msgs = @[
     @"神马都是浮云",
     @"这是什么",
     @"歌词展示",
     @"Thanks♪(･ω･)ﾉ哈哈哈哈哈"
 ];
  [[PipLyricsManager shareTool] addLastLineText:msgs[arc4random()%msgs.count]];

*/

- (void)showConsoleLogWithSuperView:(UIView *)superView;
- (void)addLastLineText:(NSString *)text;

@end

NS_ASSUME_NONNULL_END
