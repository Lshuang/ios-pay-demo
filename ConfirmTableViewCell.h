//
//  CheckOutProcessTableViewCell.h
//  SPayUI
//
//  Created by RInz on 15/3/25.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ConfirmTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UIImageView *goodImage;
@property (weak, nonatomic) IBOutlet UILabel *goodDescription;
@property (weak, nonatomic) IBOutlet UILabel *goodPrice;
@property (weak, nonatomic) IBOutlet UILabel *goodCount;

@end
