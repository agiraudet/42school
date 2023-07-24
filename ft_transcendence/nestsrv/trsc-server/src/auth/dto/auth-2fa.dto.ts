import { IsOptional, IsString, MaxLength, MinLength } from "class-validator";


export class Auth2faDto {
    @IsOptional()
    @IsString()
    @MaxLength(20)
    twoFactorAuthenticationCode: string;
}