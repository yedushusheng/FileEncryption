# FileEncryption
基于3DES、blowfish、MD5的文件加密/解密系统

使用：
1、选择待加密的文件；
2、选择加密方式：单一加密方式/两次加密方式
3、执行加密

说明：
一次加密可以分别采用3DES或者blowfish，连续加密采用先3DES后blowfish的方式

存在问题：
3DES加密与blowfish不匹配
MD5校验值追加到密文尾部并不合理
