//
//  PartnerConfig.h
//  AlipaySdkDemo
//
//  Created by ChaoGanYing on 13-5-3.
//  Copyright (c) 2013年 RenFei. All rights reserved.
//
//  提示：如何获取安全校验码和合作身份者id
//  1.用您的签约支付宝账号登录支付宝网站(www.alipay.com)
//  2.点击“商家服务”(https://b.alipay.com/order/myorder.htm)
//  3.点击“查询合作者身份(pid)”、“查询安全校验码(key)”
//

#ifndef MQPDemo_PartnerConfig_h
#define MQPDemo_PartnerConfig_h

//合作身份者id，以2088开头的16位纯数字
#define PartnerID @"2088711322600312"
//收款支付宝账号
#define SellerID  @"2088711322600312"

//安全校验码（MD5）密钥，以数字和字母组成的32位字符
#define MD5_KEY @"nvn7fcz0t3mvj6v43itwic32b7eqbh07"

//商户私钥，自助生成
#define PartnerPrivKey @"MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBAKCfeXVie9NwNzTAMGbl7YCP+waMwqbSxmhWh17spYMnQUQ9Aet1YNenI+ovCGzafYlhb17hV3m1rxq4U4vcwFbYQcDFgDJTe9ovbSRWeyhBWLsks1jZHUsPpqZ/vq8uNA5DfBipTZDmA+jVBCnbNeTdowqLI36an8ugkjAno1ZbAgMBAAECgYB9WPaoLJsFfmUWvYUISBb4ZWQ4     0FB3b7V2Z1BtO7BOkavVXObKoWdZ5A2bC+k/SaL+OxN2r9RcHvTvnTlVxIg0ARIbuBJRYQASQuOJ4gy2UMZ+z+o/ofGMaImTszzv49Ppoq4GaHvaZLmeHaLOaT8y/QX9F6n9Il8+c7XcofmrAQJBANHMco9WWmzC9u0ahzmtNhtxKBfZgjDyOW4DL5YrC/5YqYRkeDcUF6MvQpCY274cHC5IInvrn6aWP8Zh0mWLH4sCQQDD/rY8BQkttm3BeQgpYqBuZlrqsDH5z8b6tL4Bj0wMPTF1F9JO5QHEeO9Z1oWslvCMJtbFs9KO0x9mHtNJnH5xAkEAko/HzBigTPCafaMVqpY1gVA4mQirKbRdqFvzZ22lEEcyDTn+vUN9C9PdJZSTliifCzn7VSSSwFagMN9vkt5w5wJAT+r1neWjx3sCqAhVFqL7reiYm+e6iRV7GlFGxNYMeVUebJOJEth4bwes+WHq4eQuM8fGfZkEe26E+BwLpZFlUQJAHB0WAxxLU1/s5nJIcodQKDdXgwsrinyGspb/MKH0P/blsQWGaT8SNHwvrymDsKb2ylJqfRkDqTGmRLyVoL+RBw=="

//支付宝公钥
#define AlipayPubKey  @"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCnxj/9qwVfgoUh/y2W89L6BkRAFljhNhgPdyPuBV64bfQNN1PjbCzkIM6qRdKBoLPXmKKMiFYnkd6rAoprih3/PrQEB/VsW8OoM8fxn67UDYuyBTqA23MML9q1+ilIZwBC2AQ2UBVOrFXfFl75p6/B5KsiNG9zpgmLCUYuLkxpLQIDAQAB"

#endif
