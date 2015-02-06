//
//  JSenPayEngine.m
//  testAliPay
//
//  Created by JSen on 14/9/29.
//  Copyright (c) 2014年 wifitong. All rights reserved.
//

#import "JSenPayEngine.h"
#import <UIKit/UIKit.h>
#import "AFHTTPSessionManager.h"
#import "AFHTTPRequestOperationManager.h"
#import <BeeCloud/BeeCloud.h>

@implementation JSenPayEngine


+ (instancetype)sharePayEngine {
    static JSenPayEngine *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
    });
    return instance;
}

- (instancetype)init {
    if (self = [super init]) {
//        _resultSEL = @selector(paymentResult:);
    }
    return self;
}


+ (void)paymentWithInfo:(NSDictionary *)payInfo result:(paymentFinishCallBack)block {
    [[JSenPayEngine sharePayEngine] paymentWithInfo:payInfo result:block];
}

- (void)paymentWithInfo:(NSDictionary *)payInfo result:(paymentFinishCallBack)block {
    
    _outTradeNo = [JSenPayEngine generateTradeNO];
    [BCPay reqAliPayment:kTraceID outTradeNo:_outTradeNo subject:@"薯片" body:@"品客薯片" totalFee:@"0.01" scheme:kAppSchema payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"AliPay strMsg = %@", strMsg);
    }];
    
}

+ (void)refundForAli:(NSString *)out_trade_no {
    NSDate *date = [NSDate date];
    NSDateFormatter * formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *dateString = [formatter stringFromDate:date];
    [BCPay reqAliRefund:out_trade_no refundNo:dateString refundFee:@"0.01" refundReason:@"不好喝" refundBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"AliRefund strMsg = %@", strMsg);
    }];
}

#pragma mark - unionPay

+ (void)unionPayment:(UIViewController *)viewController {
    [BCPay reqUnionPayment:@"BeeCloud" body:@"自制白开水" outTradeNo:[JSenPayEngine generateTradeNO] totalFee:@"1" viewController:viewController payblock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"unionPay %s %@", __func__, strMsg);
    }];
}


+ (NSArray *)queryOrder:(NSUInteger)index {
    NSArray *array = nil;
    if (index == 0) {
        array = [BCPay queryOrderByTraceID:kTraceID channel:BCWeChatPay action:BCPayActionPayment];
    } else {
       array = [BCPay queryOrderByTraceID:kTraceID channel:BCAliPay action:BCPayActionPayment];
    }
    return array;
}

/*
 *随机生成15位订单号,外部商户根据自己情况生成订单号
 */
+ (NSString *)generateTradeNO
{
    const int N = 15;
    
    NSString *sourceString = @"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    NSMutableString *result = [[NSMutableString alloc] init];
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        unsigned index = rand() % [sourceString length];
        NSString *s = [sourceString substringWithRange:NSMakeRange(index, 1)];
        [result appendString:s];
    }
    return result;
}

#pragma mark -
#pragma mark - 微信支付过程

- (void)wxPayAction {
    [BCPay reqWXPayment:@"自制白开水" totalFee:@"1" outTradeNo:[JSenPayEngine genOutTradNo] traceID:kTraceID payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        NSLog(@"%s strMsg = %@", __func__, strMsg);
    }];
}

- (void)wxRefundAction:(NSString *)outTradeNo {
    
    NSString *outRefundNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    NSLog(@"refund no = %@", outRefundNo);
    [BCPay reqWXRefund:outTradeNo outRefundNo:outRefundNo refundReason:@"不好喝" refundFee:@"1" payBlock:^(BOOL success, NSString *errMsg, NSError *error) {
        NSLog(@"%s,%s,%d,%@", __FILE__, __func__, __LINE__, errMsg);
    }];
}
//MARK: 时间戳
+ (NSString *)genTimeStamp
{
    return [NSString stringWithFormat:@"%.0f", [[NSDate date] timeIntervalSince1970]];
}
+ (NSString *)genOutTradNo
{
    return [CommonUtil md5:[NSString stringWithFormat:@"%d", arc4random() % 10000]];
}

@end
