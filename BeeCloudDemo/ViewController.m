//
//  ViewController.m
//  BeeCloudDemo
//
//  Created by RInz on 15/2/5.
//  Copyright (c) 2015年 RInz. All rights reserved.
//

#import "ViewController.h"

@interface ViewController (){
    NSString* _out_trade_no;
}

@end

@implementation ViewController

@synthesize payButton;
@synthesize paySegment;
@synthesize listButton;
@synthesize listTableView;
@synthesize payList;
@synthesize listName;

- (void)viewDidLoad {
    [super viewDidLoad];
    self.listTableView.dataSource = self;
    self.listTableView.delegate = self;
    self.listName.text = @"请查询";
}

- (IBAction)pay:(id)sender {
    switch ([paySegment selectedSegmentIndex]) {
        case 0:
            [self wxPay];
            break;
        case 1:
            [self aliPay];
            break;
        case 2:
            [self unionPay];
        default:
            break;
    }
}

#pragma mark - 微信支付
//@"自制白开水"为:商品描述
//totalFee为:支付金额*以分为单位*
//outTradeNo为需要您自行生成的订单号,*32个字符内、包含数字与字母,确保在商户系统中唯一*可根据[[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""]获取;
//traceid为:支付用户ID,必须保证在商户系统中的唯一性
// block支付结果回调
// 通过该方法实现对各种参数的初始化，然后发起微信支付，并跳转到微信.
- (void)wxPay{
    NSString *outTradeNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    [BCPay reqWXPayment:@"自制白开水" totalFee:@"1" outTradeNo:outTradeNo traceID:@"BeeCloud01" payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            // 表明微信支付成功
        } else {
            // 表明支付过程中出现错误，strMsg为错误原因
        }
        NSLog(@"%s strMsg = %@", __func__, strMsg);
    }];
}

//outTradeNo:用户要退订的订单号
//outRefundNo:您自行生成的退订订单号,*32个字符内、包含数字与字母,确保在商户系统中唯一*可根据[[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""]获取;
//refundReason:退款原因
//refundFee:退款金额
//payBlock:发起退款结果回调， 用户在app发起退款请求成功后，商户会收到退款请求，商户可在后台确认，完成退款操作
- (void)wxRefund:(NSString*)outTradeNo{
    NSString *outRefundNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    NSLog(@"refund no = %@", outRefundNo);
    [BCPay reqWXRefund:outTradeNo outRefundNo:outRefundNo refundReason:@"不好喝" refundFee:@"1" payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            // 退款申请成功
        } else {
            // 退款失败，strMsg为错误原因
        }
        NSLog(@"%s,%s,%d,%@", __FILE__, __func__, __LINE__, error);
    }];
}

#pragma mark - 支付宝支付

//  @param trace_id     支付用户ID，必须保证在商户系统中唯一.可通过trace_id查询订单详情。
//  @param out_trade_no 商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
//  @param subject      商品的标题/交易标题/订单标 题/订单关键字等。该参数最长为 128 个汉字
//  @param body         对一笔交易的具体描述信息。如果是多种商品,请将商品描 述字符串累加传给body
//  @param total_fee    该笔订单的资金总额,单位为RMB-Yuan。取值范围为[0.01,100000000.00],精确到小数点后两位
//  @param scheme       调用支付的app注册在info.plist中的scheme
//  @param block        支付结果回调
- (void)aliPay{
    NSString *outTradeNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    [BCPay reqAliPayment:@"BeeCloud01" outTradeNo:outTradeNo subject:@"自制白开水" body:@"BeeCloud 自制白开水" totalFee:@"0.01" scheme:@"payTestDemo" payBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            // 表明支付宝支付成功
        } else {
            // 表明支付过程中出现错误，strMsg为错误原因
        }
        NSLog(@"AliPay strMsg = %@", strMsg);
    }];
}


//  根据out_trade_no，refund_no, refund_reason,refund_fee查询订单是否可退款，允许退款情况下自动生成预退款订单，否则返回不可退款原因。预退款订单生成成功后，在BeeCloud商户后台对预退款订单进行处理。（订单状态trade_status=@”TRADE_SUCCESS“)时支持退款，其他状态下不支持退款。
//  @param out_trade_no  商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
//  @param refund_no     格式为:退款日期(8位)+流水号(3~8位)。不可重复,且退款日期必须是当天日期(年月日)。
//                       流水号可以接受数字或英文字符,建议使用数字,但不可接受“000”。例如: 201101120001
//                       demo中使用8位年月日+6位时分秒组合而成
//  @param refund_fee    退款金额
//  @param refund_reason 退款原因
//  @param block         退款结果回调
- (void)aliRefund:(NSString*)out_trade_no{
    NSDate *date = [NSDate date];
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *dateString = [formatter stringFromDate:date];
    [BCPay reqAliRefund:out_trade_no refundNo:dateString refundFee:@"0.01" refundReason:@"不好吃" refundBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if(success){
            //
        }else{
            NSLog(@"Failed:%@",error.description);
        }
        NSLog(@"Msg:%@",strMsg);
    }];
}

#pragma mark - 银联支付
//  @param trace_id       支付用户ID，必须保证在商户系统中唯一.可通过trace_id查询订单详情。
//  @param body           商品的标题/交易标题/订单标题/订单关键字等。该参数最长为128个汉字
//  @param out_trade_no   商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
//  @param total_fee      支付金额,以分为单位
//  @param viewController 调起银联支付的页面,一般为self
//  @param block          接收支付结果回调
- (void)unionPay{
    NSString *outTradeNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    [BCPay reqUnionPayment:@"BeeCloud01" body:@"渣渣菜鸡" outTradeNo:outTradeNo totalFee:@"1" viewController:self payblock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            //
        }else{
            NSLog(@"UnionPay Faild:%@",error.description);
        }
        NSLog(@"Msg:%@", strMsg);
    }];
}

//  银联预退款，支持部分退款或者全额退款。如果提供的支付订单的交易状态不支持退款，在block中返回具体的信息;如果支持退款，生成预退款订单，商户在管理后台管理预退款订单。
//  @param out_trade_no  商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
//  @param refund_fee    退款金额
//  @param out_refund_no 商户系统内部的退款订单号,包含数字与字母,确保在商户系统中唯一
//  @param refund_reason 退款原因
//  @param block         接收预退款订单生成结果
- (void)unionRefund:(NSString*)outTradeNo{
    NSString *outRefundNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    [BCPay reqUnionRefund:outTradeNo refundFee:@"0.01" outRefundNo:outRefundNo refundReason:@"难吃" refundBlock:^(BOOL success, NSString *strMsg, NSError *error) {
        if (success) {
            //
        }else{
            NSLog(@"UnionRefund Faild:%@",error.description);
        }
        NSLog(@"Msg:%@", strMsg);
    }];
}

#pragma mark - 订单查询

- (IBAction)checkPayList:(id)sender {
    payList = nil;
    payList = [NSMutableArray arrayWithArray:[self queryOrder:[paySegment selectedSegmentIndex]]];
    [self.listTableView reloadData];
}

- (NSArray *)queryOrder:(NSUInteger)index {
    NSArray *array = nil;
    if (index == 0) {
        array = [BCPay queryOrderByKey:OrderKeyTraceID value:@"BeeCloud01" channelAction:BCPayWxPay];
        self.listName.text = @"微信订单";
    } else if(index == 1) {
        array = [BCPay queryOrderByKey:OrderKeyTraceID value:@"BeeCloud01" channelAction:BCPayAliPay];
        self.listName.text = @"支付宝订单";
    }else{
        array = [BCPay queryOrderByKey:OrderKeyTraceID value:@"BeeCloud01" channelAction:BCPayUPPay];
        self.listName.text = @"银联订单";
    }
    return array;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.payList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *cellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdentifier];
    }
    
    NSString * trade_status_key = (paySegment.selectedSegmentIndex==0)?@"trade_state":@"trade_status";
    cell.textLabel.text = [NSString stringWithFormat:@"%@支付金额:%@ 交易状态:%@", [[self.payList objectAtIndex:indexPath.row] objectForKey:@"trace_id"], [[self.payList objectAtIndex:indexPath.row] objectForKey:@"total_fee"], [[self.payList objectAtIndex:indexPath.row] objectForKey:trade_status_key]];
    
    [cell.textLabel setFont:[UIFont systemFontOfSize:13]];
    //total_fee out_trade_no
    cell.detailTextLabel.text = [NSString stringWithFormat:@"订单号:%@", [[self.payList objectAtIndex:indexPath.row] objectForKey:@"out_trade_no"]];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (paySegment.selectedSegmentIndex == 0) {
        if ([[self.payList[indexPath.row] objectForKey:@"trade_state"]isEqualToString:@"0"]) {
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"请求退款？" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
            _out_trade_no = [self.payList[indexPath.row] objectForKey:@"out_trade_no"];
            [alert show];
        }else{
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"该支付没有完成，不能退款" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
            _out_trade_no = nil;
            [alert show];
        }
    } else if(paySegment.selectedSegmentIndex == 1) {
        if ([[self.payList[indexPath.row] objectForKey:@"trade_status"] isEqualToString:@"TRADE_SUCCESS"]) {
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"请求退款？" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
            _out_trade_no = [self.payList[indexPath.row] objectForKey:@"out_trade_no"];
            [alert show];
        }else{
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"该支付没有完成，不能退款" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
            _out_trade_no = nil;
            [alert show];
        }
    }else if(paySegment.selectedSegmentIndex == 2){
        if ([[self.payList[indexPath.row] objectForKey:@"trade_status"] isEqualToString:@"TRADE_SUCCESS"]) {
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"请求退款？" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
            _out_trade_no = [self.payList[indexPath.row] objectForKey:@"out_trade_no"];
            [alert show];
        }else{
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"退款" message:@"该支付没有完成，不能退款" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
            _out_trade_no = nil;
            [alert show];
        }
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if(buttonIndex == 0){
        //
    }else if(buttonIndex == 1){
        if (paySegment.selectedSegmentIndex == 0){
            [self wxRefund:_out_trade_no];
        }else if (paySegment.selectedSegmentIndex == 1){
            [self aliRefund:_out_trade_no];
        }else if (paySegment.selectedSegmentIndex ==2){
            [self unionRefund:_out_trade_no];
        }
    }
}



@end
