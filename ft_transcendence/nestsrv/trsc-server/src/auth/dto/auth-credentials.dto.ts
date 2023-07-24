import { IsAlphanumeric, IsEmail, IsOptional, IsString, Matches, MaxLength, MinLength } from "class-validator";

export class AuthCredentialsDto{
    @IsString()
    @MinLength(4)
    @MaxLength(20)
    @IsAlphanumeric()
    username: string;

    @IsString()
    @MinLength(4)
    @MaxLength(20)
    @Matches(/((?=.*\d)|(?=.*\W+))(?![.\n])(?=.*[A-Z])(?=.*[a-z]).*$/, {
        message: 'Your password is weak'})
    password: string;

    @IsEmail()
    email: string;
}