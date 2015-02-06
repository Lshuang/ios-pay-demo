//
//  AppDelegate.m
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import "AppDelegate.h"
#import "JSenPayEngine.h"
#import <BeeCloud/BeeCloud.h>
@interface AppDelegate ()//<WXApiDelegate>

@end

@implementation AppDelegate
@synthesize nav, controllerView;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    [BeeCloud initWithAppKey:@"39a7a518-9ac8-4a9e-87bc-7885f33cf18c"];
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    controllerView = [[ViewController alloc] init];
    nav = [[UINavigationController alloc] initWithRootViewController:controllerView];
    self.window.rootViewController = nav;
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
    
    
    
    return YES;
}

/*
 sourceApplication:
 
 1.com.tencent.xin
 
 2.com.alipay.safepayclient
 */

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
//    return  [WXApi handleOpenURL:url delegate:self];
    return [BCPay handleOpenUrl:url withBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"strMsg = %@", strMsg);
    }];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    NSLog(@"source app-%@, des app-%@",sourceApplication,application);
    
    return[BCPay handleOpenUrl:url withBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"strMsg = %@", strMsg);}];//0.successed -2.cancel
        
//    if ([sourceApplication isEqualToString:@"com.tencent.xin"]) {
//        return [BCPay handleOpenUrl:url withBlock:^(BOOL success, NSString *strMsg, NSError *error) {
//            NSLog(@"strMsg = %@", strMsg);//0.successed -2.cancel
//        }];
//    }
//    else if ([sourceApplication isEqualToString:@"com.alipay.iphoneclient"]) {
//         [self parse:url application:application];
//        return YES;
//    }
    
}

//- (void)onResp:(BaseResp *)resp
//{
//    NSLog(@"%@",resp);
//    if ([resp isKindOfClass:[PayResp class]]) {
//        
//        NSString *strTitle = [NSString stringWithFormat:@"支付结果"];
//        NSString *strMsg = [NSString stringWithFormat:@"errcode:%d", resp.errCode];
//        
//        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:strTitle
//                                                        message:strMsg
//                                                       delegate:self
//                                              cancelButtonTitle:@"OK"
//                                              otherButtonTitles:nil, nil];
//        [alert show];
//        
//      
//    }
//}

//- (void)parse:(NSURL *)url application:(UIApplication *)application {
//    
//    //结果处理
//    AlixPayResult* result = [self handleOpenURL:url];
//    
//    if (result)
//    {
//        if (result.statusCode == 9000)
//        {
//            /*
//             *用公钥验证签名 严格验证请使用result.resultString与result.signString验签
//             */
//            
//            //交易成功
//           // NSString* key = @"签约帐户后获取到的支付宝公钥";
//            id<DataVerifier> verifier;
//            verifier = CreateRSADataVerifier(AlipayPubKey);
//            
//            if ([verifier verifyString:result.resultString withSign:result.signString])
//            {
//                //验证签名成功，交易结果无篡改
//                NSLog(@"签名认证成功");
//                
//            }
//            
//        }
//        else
//        {
//            //交易失败
//        }
//    }
//    else
//    {
//        //失败
//    }
//    
//}

//- (AlixPayResult *)resultFromURL:(NSURL *)url {
//    NSString * query = [[url query] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
//
//    return [[AlixPayResult alloc] initWithString:query];
//
//}
//
//- (AlixPayResult *)handleOpenURL:(NSURL *)url {
//    AlixPayResult * result = nil;
//    
//    if (url != nil && [[url host] compare:@"safepay"] == 0) {
//        result = [self resultFromURL:url];
//    }
//    
//    return result;
//}

@end
