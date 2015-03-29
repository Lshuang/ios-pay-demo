//
//  ShoppingCartTableViewCell.m
//  SPayUI
//
//  Created by RInz on 15/3/24.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import "ShoppingCartTableViewCell.h"

@implementation ShoppingCartTableViewCell{
    NSDictionary *dict;
}

- (IBAction)remove:(id)sender {
    self.productCount -= 1;
    self.countLabel.text = [NSString stringWithFormat:@"%d",self.productCount];
    
    if (self.productCount == 1) {
        self.removeButton.enabled = false;
    }

    [[NSNotificationCenter defaultCenter]postNotificationName:@"removeCount" object:self userInfo:@{@"price":[NSString stringWithFormat:@"%f",self.productPrice],@"row":@(self.index)}];
}

- (IBAction)add:(id)sender {
    self.productCount += 1;
    self.countLabel.text = [NSString stringWithFormat:@"%d",self.productCount];
    
    if (self.productCount > 1) {
        self.removeButton.enabled = true;
    }
    [[NSNotificationCenter defaultCenter]postNotificationName:@"addCount" object:self userInfo:@{@"price":[NSString stringWithFormat:@"%f",self.productPrice],@"row":@(self.index)}];
}

@end
