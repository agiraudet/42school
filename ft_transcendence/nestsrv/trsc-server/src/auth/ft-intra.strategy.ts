// The Injectable decorator marks it as a provider that can be managed by Nest IoC container.
import { HttpModule, HttpService } from '@nestjs/axios';
import { Injectable, } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';

// The PassportStrategy imported from NestJS Passport, allows to easily integrate Passport strategies within your NestJS application.
import { PassportStrategy } from '@nestjs/passport';

// The Strategy from 'passport-oauth2' provides mechanisms to handle OAuth2 process with ease.
import { Strategy } from 'passport-oauth2';
import { firstValueFrom } from 'rxjs';
import { Any } from 'typeorm';

@Injectable() // Makes this class as a NestJS Provider.
export class SchoolIntranetStrategy extends PassportStrategy(Strategy, 'school') {

  // Constructor of the class, calling the parent (PassportStrategy) constructor
  constructor(
    private httpService: HttpService,
    private config: ConfigService,
  ) {
    super({
      // URL that users will be redirected to in order to give your app permission to access their data.
      authorizationURL: config.get('AUTH_URL'),

      // URL that your app will send the user's code to in order to exchange it for an access token.
      tokenURL: config.get('TOK_URL'),

      // Your app's client ID, issued when you created a new app within your OAuth provider.
      clientID: config.get('CLI_ID'),

      // Your app's client secret, issued when you created a new app within your OAuth provider.
      clientSecret: config.get('CLI_SECRET'),

      // The URL that users will be redirected to after they have authenticated with the provider.
      callbackURL: config.get('CB_URL'),

      // The scopes that you want to request from the provider.
      scope: '',
    });
  }

  // The validate method that you need to implement, which Passport will call once the user allowed access.
  async validate(accessToken: string, refreshToken: string, profile: any, done: (err?: any, user?: any) => void): Promise<any> {

    // Extracting data from the profile object received.
    const { email, login } = profile;

    // Constructing user object with data extracted from the profile.
    const user = {
      email: email,
      login: login,
      accessToken
    };
    const headers = { Authorization: `Bearer ${accessToken}` };
    const response$ = await this.httpService.get('https://api.intra.42.fr/v2/me', { headers });
    const response = await firstValueFrom(response$);
    const user1 = {
      email: response.data.email,
      username: response.data.login,
      id: response.data.id,
      accessToken,
    }

    // Done is a function from passport, signaling Passport that it can serialize this user object to session or pass to req.user.
    done(null, user1);
  }
}
