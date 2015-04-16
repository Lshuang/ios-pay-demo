//
//  PaymentListViewController.m
//  SPayUI
//
//  Created by 钱志浩 on 15/4/16.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import "PaymentListViewController.h"

@interface PaymentListViewController ()

@end

@implementation PaymentListViewController

@synthesize listTableView;
@synthesize payList;
@synthesize paySegment;

- (void)viewDidLoad {
    [super viewDidLoad];
    self.listTableView.delegate = self;
    self.listTableView.dataSource = self;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)checkPayList:(id)sender {
    payList = nil;
    payList = [NSMutableArray arrayWithArray:[self queryOrder:[paySegment selectedSegmentIndex]]];
    [self.listTableView reloadData];
}

- (NSArray *)queryOrder:(NSUInteger)index {
    NSArray *array = nil;
    if (index == 0) {
        array = [BCWXPay queryWXPayOrderByKey:OrderKeyTraceID value:@"BeeCloudSPay" orderType:BCPayWxPay];
    } else if(index == 1) {
        array = [BCAliPay queryAliOrderByKey:OrderKeyTraceID value:@"BeeCloudSPay" orderType:BCPayAliPay];
    }else{
        array = [BCUnionPay queryUPOrderByKey:OrderKeyTraceID value:@"BeeCloudSPay" orderType:BCPayUPPay];
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
    
    NSString * status = [[self.payList objectAtIndex:indexPath.row] objectForKey:@"trade_state"];
    if ([status  isEqual: @"TRADE_CANCEL"]) {
        status = @"取消";
    }else if ([status isEqual:@"TRADE_SUCCESS"]){
        status = @"成功";
    }else if ([status isEqual:@"TRADE_FAILED"]){
        status = @"失败";
    }
    cell.textLabel.attributedText = [[NSMutableAttributedString alloc]initWithString:[NSString stringWithFormat:@"购买者:%@ 金额:%@ 交易状态:%@", [[self.payList objectAtIndex:indexPath.row] objectForKey:@"trace_id"], [[self.payList objectAtIndex:indexPath.row] objectForKey:@"total_fee"], status]];
    
    [cell.textLabel setFont:[UIFont systemFontOfSize:13]];
    //total_fee out_trade_no
    cell.detailTextLabel.text = [NSString stringWithFormat:@"订单号:%@", [[self.payList objectAtIndex:indexPath.row] objectForKey:@"out_trade_no"]];
    return cell;
}

@end
